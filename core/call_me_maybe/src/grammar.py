# ABOUTME: Grammar "steps" -- the building blocks the constrained decoder walks through.
# ABOUTME: Each step knows, at every point, exactly which token ids would keep the output
# ABOUTME: both syntactically valid JSON and compliant with the function-calling schema; every
# ABOUTME: other token is masked out (logit -> -inf) before a choice is made.

"""The constrained-decoding grammar itself -- this is the core of the project.

Brief
-----
A "grammar step" is one unit of generation with a well-defined job:

* :class:`LiteralStep` emits fixed text (structural JSON punctuation, key
  names) with no model choice involved at all.
* :class:`EnumStep` forces the model to spell out exactly one of a fixed set
  of strings (function names; also reused by :class:`JSONBooleanStep` for
  ``true``/``false``).
* :class:`JSONStringStep` generates a quoted JSON string value, one token at
  a time, never allowing an unescaped quote/backslash/control character.
* :class:`JSONNumberStep` generates a JSON number, one token at a time,
  following RFC 8259's number grammar exactly (see the regex block below).

`function_caller.py` chains these steps together into a full per-prompt plan
(name -> parameters) driven by a function's declared schema. Every step
follows the same pattern: look at the vocabulary, work out which token ids
would keep the output valid, mask everything else via
`decoder.masked_argmax`, and repeat until the step's own stop condition is
met.
"""

from __future__ import annotations

import re
from dataclasses import dataclass
from typing import Any, Protocol

from .decoder import (
    append,
    encode_literal,
    masked_argmax,
    next_token_logits,
    unconstrained_top_token_id,
)
from .errors import GenerationError
from .vocabulary import Vocabulary

# JSON number grammar (RFC 8259 section 6): sign, then a *mandatory* integer
# part, then an optional fraction, then an optional exponent -- in that order.
# The three prefix patterns below deliberately do NOT make the integer part
# optional once a fraction or exponent marker is present: "-." or ".5" must
# never be treated as valid partial JSON numbers, or the decoder could wander
# into a state (e.g. "-.000...") that can never be completed.
_INT_PREFIX_RE = re.compile(r"\A-?(0|[1-9][0-9]*)?\Z")
_FRAC_PREFIX_RE = re.compile(r"\A-?(0|[1-9][0-9]*)\.[0-9]*\Z")
_EXP_PREFIX_RE = re.compile(r"\A-?(0|[1-9][0-9]*)(\.[0-9]+)?[eE][+-]?[0-9]*\Z")
_NUMBER_COMPLETE_RE = re.compile(r"\A-?(0|[1-9][0-9]*)(\.[0-9]+)?([eE][+-]?[0-9]+)?\Z")


def _is_number_prefix(text: str) -> bool:
    """True if `text` could still become a valid JSON number by appending
    more characters (or already is one) -- i.e. it's a legal *partial* state
    for `JSONNumberStep`, checked against all three RFC 8259 prefix shapes
    (still-building-the-integer-part, has-a-dot, has-an-exponent-marker)."""
    return bool(
        _INT_PREFIX_RE.fullmatch(text)
        or _FRAC_PREFIX_RE.fullmatch(text)
        or _EXP_PREFIX_RE.fullmatch(text)
    )


# Characters that must never appear un-escaped inside a JSON string body.
_FORBIDDEN_IN_STRING = ('"', "\\", "\n", "\r", "\t")

_MAX_NUMBER_TOKENS = 24
_MAX_STRING_TOKENS = 80
_MAX_ENUM_TOKENS = 40


class Model(Protocol):
    """The subset of the llm_sdk model interface every grammar step needs."""

    def encode(self, text: str) -> Any:
        """Tokenize `text` into ids."""
        ...

    def get_logits_from_input_ids(self, input_ids: list[int]) -> list[float]:
        """Next-token logits for the sequence so far."""
        ...


@dataclass
class LiteralStep:
    """Emits fixed text with no model involvement in *what* is produced --
    only the model still has to *see* these tokens, so they stay in context
    for whatever comes next."""

    text: str

    def run(self, model: Model, vocabulary: Vocabulary, input_ids: list[int]) -> tuple[str, list[int]]:
        """Encode `self.text` and append it to `input_ids` unconditionally.

        Parameters
        ----------
        model : Model
            Used only to tokenize `self.text` -- no logits are fetched.
        vocabulary : Vocabulary
            Unused here (accepted so every step shares one call signature,
            letting `function_caller.py` treat all steps uniformly).
        input_ids : list[int]
            Token ids generated so far.

        Returns
        -------
        tuple[str, list[int]]
            The literal text (unchanged) and the extended id list.
        """
        ids = encode_literal(model, self.text)
        return self.text, input_ids + ids


@dataclass
class EnumStep:
    """Forces the model to emit exactly one of a fixed set of literal strings
    (e.g. a function name, or JSON's `true`/`false`). This is the schema-level
    constraint the subject calls out explicitly: fields with a fixed set of
    legal values must never let the model wander outside that set."""

    options: list[str]

    def run(self, model: Model, vocabulary: Vocabulary, input_ids: list[int]) -> tuple[str, list[int]]:
        """Generate tokens until the accumulated text exactly equals one of
        `self.options`.

        Because tokens rarely align with option boundaries (a function name
        might be spelled out in one merged token or several single-character
        ones -- see `tests/conftest.py`'s fake vocabulary for both cases),
        this works by narrowing a set of `remaining` candidate options after
        every token: any vocabulary token whose text would still keep the
        accumulated string a *prefix* of at least one remaining option stays
        eligible; everything else is masked out.

        Parameters
        ----------
        model : Model
            Supplies logits at each step.
        vocabulary : Vocabulary
            Source of every candidate token's literal text.
        input_ids : list[int]
            Token ids generated so far (grows by one token per iteration).

        Returns
        -------
        tuple[str, list[int]]
            The exact option string that was generated, and the extended id
            list (including the tokens that spelled it out).

        Raises
        ------
        GenerationError
            If constructed with zero options, if no vocabulary token can
            extend the current partial text towards any remaining option
            (a vocabulary/grammar mismatch), or if generation runs for
            `_MAX_ENUM_TOKENS` steps without landing on a complete option.
        """
        if not self.options:
            raise GenerationError("EnumStep created with zero options")

        remaining = list(self.options)
        text = ""
        for _ in range(_MAX_ENUM_TOKENS):
            # A token is a legal next choice iff appending its text still
            # leaves us a strict prefix of at least one option we haven't
            # ruled out yet.
            candidates: dict[int, str] = {}
            for token_id, token_text in vocabulary.items():
                if not token_text:
                    continue
                candidate = text + token_text
                if any(option.startswith(candidate) for option in remaining):
                    candidates[token_id] = token_text
            if not candidates:
                raise GenerationError(
                    f"no vocabulary token continues any of the allowed options {self.options!r} "
                    f"from partial text {text!r}"
                )

            logits = next_token_logits(model, input_ids)
            chosen_id = masked_argmax(logits, candidates.keys())
            chosen_text = candidates[chosen_id]
            input_ids = append(model, input_ids, chosen_id)
            text += chosen_text
            # Narrow the candidate set for the next iteration.
            remaining = [option for option in remaining if option.startswith(text)]

            if text in self.options:
                return text, input_ids

        raise GenerationError(f"enum generation did not converge on one of {self.options!r} (got {text!r})")


@dataclass
class JSONStringStep:
    """Generates the *contents* of a JSON string, including the surrounding
    quotes. To keep the grammar simple and fully correct without a general
    escape-sequence parser, generated string bodies may not themselves contain
    a literal backslash, double quote, or raw control character -- more than
    enough for the plain text this project's functions deal with (names,
    greetings, reversed words, regex replacement text). See README / Design
    decisions for the rationale.
    """

    def run(self, model: Model, vocabulary: Vocabulary, input_ids: list[int]) -> tuple[str, list[int]]:
        """Emit an opening quote, then generate body tokens until the model
        chooses the closing-quote token.

        Parameters
        ----------
        model : Model
            Supplies logits at each step.
        vocabulary : Vocabulary
            Source of every candidate token's literal text.
        input_ids : list[int]
            Token ids generated so far.

        Returns
        -------
        tuple[str, list[int]]
            The string's *contents* (quotes excluded) and the extended id
            list (quotes included, since the model needs to see them).

        Raises
        ------
        GenerationError
            If the vocabulary has no standalone ``"`` token to close with, or
            the string runs past `_MAX_STRING_TOKENS` without the model
            choosing to close it (a real model, unlike a flat/neutral test
            double, will naturally prefer to close once content is done --
            see `tests/conftest.py::scripted_string_target` for how tests
            simulate that preference).
        """
        opening_ids = encode_literal(model, '"')
        input_ids = input_ids + opening_ids
        body = ""

        for _ in range(_MAX_STRING_TOKENS):
            # Every step re-scans the vocabulary: any token free of quotes,
            # backslashes, and control characters is a legal body extension;
            # the standalone `"` token (if present) is always offered too, as
            # the signal to stop.
            candidates: dict[int, str] = {}
            closing_id: int | None = None
            for token_id, token_text in vocabulary.items():
                if not token_text:
                    continue
                if token_text == '"':
                    closing_id = token_id
                    continue
                if any(ch in _FORBIDDEN_IN_STRING for ch in token_text):
                    continue
                candidates[token_id] = token_text

            allowed = dict(candidates)
            if closing_id is not None:
                allowed[closing_id] = '"'
            if not allowed:
                raise GenerationError("vocabulary has no usable tokens to close a JSON string")

            logits = next_token_logits(model, input_ids)
            chosen_id = masked_argmax(logits, allowed.keys())
            input_ids = append(model, input_ids, chosen_id)

            if chosen_id == closing_id:
                return body, input_ids

            body += allowed[chosen_id]

        raise GenerationError(
            f"string value exceeded {_MAX_STRING_TOKENS} tokens without closing (got {body!r})"
        )


@dataclass
class JSONNumberStep:
    """Generates a JSON number. Numbers have no delimiter of their own, so we
    need an explicit stop rule: once the digits generated so far already form
    a complete, valid JSON number, we stop as soon as the model's own
    (unconstrained) preference for the next token would fall outside the
    number grammar anyway -- i.e. we let the model tell us when it's done,
    but never let it emit something structurally invalid while doing so.
    """

    def run(self, model: Model, vocabulary: Vocabulary, input_ids: list[int]) -> tuple[str, list[int]]:
        """Generate digits (and optional sign/fraction/exponent) until the
        model signals it's done or a safety cap is hit.

        Parameters
        ----------
        model : Model
            Supplies logits at each step (including the *unconstrained* top
            choice used for the stop check below).
        vocabulary : Vocabulary
            Source of every candidate token's literal text.
        input_ids : list[int]
            Token ids generated so far.

        Returns
        -------
        tuple[str, list[int]]
            The number as text (e.g. ``"42"``, ``"-3.5"``) and the extended
            id list. Callers (`function_caller._coerce`) turn this text into
            an actual Python `int`/`float`.

        Raises
        ------
        GenerationError
            If no token can validly extend an incomplete number (a
            vocabulary/grammar mismatch), or `_MAX_NUMBER_TOKENS` is reached
            without ever reaching a complete, valid number.
        """
        text = ""
        for _ in range(_MAX_NUMBER_TOKENS):
            logits = next_token_logits(model, input_ids)

            # Legal continuations: every token whose text keeps the number a
            # valid RFC 8259 *prefix* (see `_is_number_prefix`).
            candidates: dict[int, str] = {}
            for token_id, token_text in vocabulary.items():
                if not token_text:
                    continue
                if _is_number_prefix(text + token_text):
                    candidates[token_id] = token_text

            complete = bool(_NUMBER_COMPLETE_RE.fullmatch(text))
            if complete:
                # Numbers have no closing delimiter, so "should we stop?" is
                # answered by asking the model itself: if its top choice with
                # *no* masking applied would leave the number grammar anyway
                # (e.g. it wants "," or a space next), that's our stop signal.
                top_id = unconstrained_top_token_id(logits)
                top_text = vocabulary.text_of(top_id)
                if not _is_number_prefix(text + top_text):
                    return text, input_ids

            if not candidates:
                if complete:
                    return text, input_ids
                raise GenerationError(f"no valid continuation for JSON number (partial: {text!r})")

            chosen_id = masked_argmax(logits, candidates.keys())
            input_ids = append(model, input_ids, chosen_id)
            text += candidates[chosen_id]

        # Safety cap reached: accept if what we have is already valid,
        # otherwise this is a real failure worth surfacing.
        if _NUMBER_COMPLETE_RE.fullmatch(text):
            return text, input_ids
        raise GenerationError(f"number generation did not converge on a valid JSON number (got {text!r})")


class JSONBooleanStep(EnumStep):
    """A JSON boolean is just an enum of two literal strings -- reuse
    `EnumStep` with `options` fixed to ``["true", "false"]`` rather than
    duplicating the token-assembly logic."""

    def __init__(self) -> None:
        super().__init__(options=["true", "false"])
