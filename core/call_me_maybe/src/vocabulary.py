# ABOUTME: Turns the model's raw vocabulary file into an id -> text lookup table.
# ABOUTME: Implements the standard GPT-2 / Qwen byte-level BPE alphabet by hand so this module
# ABOUTME: never has to import torch/transformers/huggingface (forbidden by the subject) -- it
# ABOUTME: only needs `json`, which is explicitly allowed.

"""Model vocabulary loading and byte-level BPE (de)coding.

Brief
-----
The constrained decoder needs to know, for every token id the model can
produce, what literal text that id represents -- that's the whole basis for
masking (`grammar.py` asks "does this token's *text* keep the output valid?").
`llm_sdk` only hands back a *path* to a vocabulary file, not a ready-made
id -> text map, and the file itself is keyed by a byte-level-encoded token
string (the same scheme GPT-2 and Qwen's tokenizers use), not plain text.
This module does two things: (1) build that id -> text map once per run via
:class:`Vocabulary`, and (2) implement the byte-level encode/decode by hand
(`encode_bpe_token` / `decode_bpe_token`), since importing `transformers` to
do it for us is against the subject's rules.
"""

from __future__ import annotations

import json
from functools import lru_cache
from pathlib import Path
from typing import ItemsView, Protocol

from .errors import InputFileError


class SupportsVocabPaths(Protocol):
    """The subset of the llm_sdk model interface this module depends on."""

    def get_path_to_vocab_file(self) -> str:
        """Return the local filesystem path to the model's ``vocab.json``."""
        ...

    def get_path_to_tokenizer_file(self) -> str:
        """Return the local filesystem path to the model's ``tokenizer.json``
        (used as a fallback when ``vocab.json`` isn't available)."""
        ...


@lru_cache(maxsize=1)
def _byte_to_unicode() -> dict[int, str]:
    """Reproduce the byte-level BPE alphabet used by GPT-2-family tokenizers
    (which Qwen's tokenizer is built on). Maps each of the 256 byte values to a
    printable unicode character, so every token can be represented in a JSON
    string without escaping issues. This is the well-known mapping originally
    published alongside GPT-2's ``encoder.py``.
    """
    bs = (
        list(range(ord("!"), ord("~") + 1))
        + list(range(ord("\xa1"), ord("\xac") + 1))
        + list(range(ord("\xae"), ord("\xff") + 1))
    )
    cs = bs[:]
    n = 0
    for b in range(256):
        if b not in bs:
            bs.append(b)
            cs.append(256 + n)
            n += 1
    return dict(zip(bs, (chr(c) for c in cs)))


@lru_cache(maxsize=1)
def _unicode_to_byte() -> dict[str, int]:
    return {v: k for k, v in _byte_to_unicode().items()}


def encode_bpe_token(text: str) -> str:
    """Inverse of :func:`decode_bpe_token`: turn raw text into the byte-level
    unicode form a GPT-2/Qwen-style vocab.json would use as a key. Mainly
    useful for building synthetic vocabularies in tests.
    """
    table = _byte_to_unicode()
    return "".join(table[b] for b in text.encode("utf-8"))


def decode_bpe_token(token: str) -> str:
    """Convert one byte-level-BPE vocabulary entry (e.g. ``'ĠHello'``) back into
    the raw text it represents (``' Hello'``). Falls back to the literal token
    for any character outside the byte-level alphabet (e.g. tokenizer special
    tokens like ``<|endoftext|>``, which are not byte-encoded).
    """
    table = _unicode_to_byte()
    raw = bytearray()
    literal_tail: list[str] = []
    for ch in token:
        if ch in table:
            raw.append(table[ch])
        else:
            literal_tail.append(ch)
    text = raw.decode("utf-8", errors="replace") if raw else ""
    return text + "".join(literal_tail)


class Vocabulary:
    """Maps token ids to the literal text they decode to.

    Built once per run from whatever vocabulary file the SDK exposes, then reused
    for every generation step (masking logits against ~150k tokens is the hot
    path, so we precompute everything that doesn't depend on decoder state).
    """

    def __init__(self, id_to_text: dict[int, str]) -> None:
        """Wrap an already-built id -> text map. Prefer :meth:`from_model`
        over calling this directly -- it handles locating and parsing the
        vocabulary file for you."""
        self._id_to_text = id_to_text

    def __len__(self) -> int:
        """Number of tokens in the vocabulary."""
        return len(self._id_to_text)

    def text_of(self, token_id: int) -> str:
        """Return the literal text a token id decodes to, or ``""`` if the
        id isn't in the vocabulary (defensive default -- an unknown id should
        never be treated as a crash-worthy condition here)."""
        return self._id_to_text.get(token_id, "")

    def items(self) -> "ItemsView[int, str]":
        """Iterate over every ``(token_id, text)`` pair -- this is what every
        grammar step in `grammar.py` scans on each generation step to build
        its candidate set."""
        return self._id_to_text.items()

    @classmethod
    def from_model(cls, model: SupportsVocabPaths) -> "Vocabulary":
        """Build a :class:`Vocabulary` from whatever the model's SDK exposes.

        Tries the plain ``vocab.json`` file first (a flat ``token string ->
        id`` map), and falls back to the fast-tokenizer ``tokenizer.json``
        (``data["model"]["vocab"]``) if the model's tokenizer doesn't expose a
        standalone vocab file. This is the only entry point calling code
        outside this module should use.

        Parameters
        ----------
        model : SupportsVocabPaths
            Anything exposing ``get_path_to_vocab_file`` /
            ``get_path_to_tokenizer_file`` -- in practice, an
            ``llm_sdk.Small_LLM_Model`` instance.

        Returns
        -------
        Vocabulary

        Raises
        ------
        InputFileError
            If neither vocabulary source could be loaded or parsed.
        """
        try:
            return cls._from_vocab_file(model.get_path_to_vocab_file())
        except Exception as vocab_error:  # noqa: BLE001 - deliberately broad, we fall back
            try:
                return cls._from_tokenizer_file(model.get_path_to_tokenizer_file())
            except Exception as tokenizer_error:  # noqa: BLE001
                raise InputFileError(
                    "Could not load a usable vocabulary from the model "
                    f"(vocab_file error: {vocab_error}; tokenizer_file error: {tokenizer_error})"
                ) from tokenizer_error

    @classmethod
    def _from_vocab_file(cls, path: str) -> "Vocabulary":
        """Parse a standalone ``vocab.json`` (``{token_string: token_id}``)."""
        with Path(path).open("r", encoding="utf-8") as handle:
            token_to_id: dict[str, int] = json.load(handle)
        # Decode every key up front (once per run) so later lookups are O(1)
        # dict access rather than repeating the byte-level decode per step.
        id_to_text = {token_id: decode_bpe_token(token) for token, token_id in token_to_id.items()}
        return cls(id_to_text)

    @classmethod
    def _from_tokenizer_file(cls, path: str) -> "Vocabulary":
        """Parse a fast-tokenizer ``tokenizer.json``, pulling the vocab map
        out of its ``model.vocab`` section."""
        with Path(path).open("r", encoding="utf-8") as handle:
            data = json.load(handle)
        token_to_id: dict[str, int] = data["model"]["vocab"]
        id_to_text = {token_id: decode_bpe_token(token) for token, token_id in token_to_id.items()}
        return cls(id_to_text)
