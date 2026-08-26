# ABOUTME: Low-level primitives shared by every constrained-decoding grammar step:
# ABOUTME: fetching logits, masking out disallowed tokens, and picking a winner.

"""Shared, model-facing primitives for constrained decoding.

Brief
-----
This is the thin layer between `grammar.py`'s steps and the raw
``llm_sdk.Small_LLM_Model`` interface: normalizing whatever `encode()` returns
into a plain list of ints, fetching logits as a numpy array, and -- the actual
"constrained" part of constrained decoding -- picking the highest-logit token
out of a restricted candidate set (`masked_argmax`). Every grammar step in
`grammar.py` is built out of these functions rather than talking to numpy or
the model directly, so the masking logic only has to be gotten right once.
"""

from __future__ import annotations

from typing import Any, Iterable, Protocol

import numpy as np

from .errors import GenerationError


class SupportsGeneration(Protocol):
    """The subset of the llm_sdk model interface the decoder needs."""

    def encode(self, text: str) -> Any:
        """Tokenize `text`, returning token ids (list[int] or a tensor)."""
        ...

    def get_logits_from_input_ids(self, input_ids: list[int]) -> list[float]:
        """Return raw (pre-softmax) logits for the token that would follow
        `input_ids`, one score per vocabulary entry."""
        ...


def to_id_list(encoded: Any) -> list[int]:
    """Normalize whatever `model.encode()` returns (a list, or a torch tensor)
    into a plain list[int], without importing torch."""
    if hasattr(encoded, "tolist"):
        value = encoded.tolist()
        # encode() returns a 2-D tensor ([1, seq_len]); flatten if needed.
        if value and isinstance(value[0], list):
            return [int(x) for x in value[0]]
        return [int(x) for x in value]
    return [int(x) for x in encoded]


def next_token_logits(model: SupportsGeneration, input_ids: list[int]) -> np.ndarray:
    """Fetch next-token logits from the model and wrap them as a numpy array
    (so `masked_argmax` and friends get fast, uniform indexing regardless of
    whatever container type the SDK happens to return)."""
    raw = model.get_logits_from_input_ids(input_ids)
    return np.asarray(raw, dtype=np.float64)


def unconstrained_top_token_id(logits: np.ndarray) -> int:
    """The model's own top pick with *no* masking applied -- used only by
    `JSONNumberStep` in `grammar.py` to detect "the model wants to stop
    generating digits now" (see that module for why numbers need this)."""
    return int(np.argmax(logits))


def masked_argmax(logits: np.ndarray, candidate_ids: Iterable[int]) -> int:
    """Pick the highest-logit token among `candidate_ids` -- this *is* the
    constrained-decoding step: every id not in `candidate_ids` is effectively
    set to -inf and excluded from the choice.

    Parameters
    ----------
    logits : np.ndarray
        Full next-token logit vector from the model (one score per vocab id).
    candidate_ids : Iterable[int]
        The token ids a grammar step has determined are structurally legal
        right now -- everything else is implicitly masked out by never being
        considered here.

    Returns
    -------
    int
        The id of the highest-scoring candidate.

    Raises
    ------
    GenerationError
        If `candidate_ids` is empty -- this would mean a grammar step
        computed zero legal continuations, which should never happen with a
        correct grammar and a vocabulary that covers basic JSON punctuation.
    """
    best_id: int | None = None
    best_score = float("-inf")
    for token_id in candidate_ids:
        score = float(logits[token_id])
        if score > best_score:
            best_score = score
            best_id = token_id
    if best_id is None:
        raise GenerationError("no valid token available for this generation step (grammar/vocab mismatch)")
    return best_id


def append(model: SupportsGeneration, input_ids: list[int], token_id: int) -> list[int]:
    """Return a new input-id list with `token_id` appended.

    Takes `model` for symmetry with the other helpers here (and in case a
    future SDK needs to touch the model when extending context); it isn't
    used by the current implementation. Returns a new list rather than
    mutating in place so callers can keep the pre-append `input_ids` around
    if they need to (e.g. for error messages).
    """
    return input_ids + [token_id]


def encode_literal(model: SupportsGeneration, text: str) -> list[int]:
    """Tokenize a fixed, known string (e.g. `'{"name": "'`) into token ids.
    Thin wrapper around `model.encode` + `to_id_list` used by `LiteralStep`
    and by every grammar step that needs to emit a literal (like the closing
    quote of a JSON string)."""
    return to_id_list(model.encode(text))
