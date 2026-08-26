# ABOUTME: Shared pytest fixtures -- a small synthetic vocabulary and a fake Small_LLM_Model that
# ABOUTME: implements the same interface as llm_sdk without needing network access or a real model.

from __future__ import annotations

import json
import string
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from src.vocabulary import Vocabulary, encode_bpe_token  # noqa: E402

# A modest set of literal pieces: every single character we need, plus a
# handful of multi-character "merges" so the tests exercise multi-token
# assembly the same way a real BPE vocabulary would.
_SINGLE_CHAR_PIECES = list(string.ascii_letters) + list(string.digits) + list(
    ' {}[]":,.-_()\'?\n'
)
_MERGED_PIECES = [
    "fn_", "add", "_numbers", "greet", "reverse", "_string", "true", "false",
    "12", "23", "34", "45", "th", "er", "in", "he", "ing",
]


class FakeSmallLLMModel:
    """Stand-in for llm_sdk.Small_LLM_Model. Tokenizes via greedy longest-match
    over a small fixed vocabulary, and returns logits built from a caller-supplied
    per-text bonus table so tests can steer (or deliberately not steer) generation.
    """

    def __init__(
        self,
        pieces: list[str],
        text_bonus: dict[str, float] | None = None,
        dynamic_bonus=None,
    ) -> None:
        unique_pieces = sorted(set(pieces), key=lambda p: (len(p), p))
        self.text_to_id = {piece: idx for idx, piece in enumerate(unique_pieces)}
        self.id_to_text = {idx: piece for piece, idx in self.text_to_id.items()}
        self.text_bonus = text_bonus or {}
        # Optional callable(input_ids) -> dict[str, float]: lets a test simulate a
        # model whose preference depends on what's been generated so far (e.g. "the
        # 'a' parameter is already filled in with 2, so now prefer producing 3").
        self.dynamic_bonus = dynamic_bonus
        self.vocab_size = len(self.text_to_id)
        self._vocab_json_path: str | None = None

    # -- llm_sdk.Small_LLM_Model interface -----------------------------------
    def encode(self, text: str) -> list[int]:
        ids: list[int] = []
        i = 0
        pieces_by_len = sorted(self.text_to_id.keys(), key=len, reverse=True)
        while i < len(text):
            for piece in pieces_by_len:
                if piece and text.startswith(piece, i):
                    ids.append(self.text_to_id[piece])
                    i += len(piece)
                    break
            else:
                raise AssertionError(f"fake tokenizer has no piece covering {text[i:i + 10]!r}")
        return ids

    def decode(self, ids: list[int]) -> str:
        return "".join(self.id_to_text[i] for i in ids)

    def get_logits_from_input_ids(self, input_ids: list[int]) -> list[float]:
        extra = self.dynamic_bonus(input_ids) if self.dynamic_bonus else {}
        logits = [0.0] * self.vocab_size
        for token_id, text in self.id_to_text.items():
            # deterministic small tie-breaker so ties never depend on dict order
            base = -0.001 * token_id
            logits[token_id] = base + self.text_bonus.get(text, 0.0) + extra.get(text, 0.0)
        return logits

    def get_path_to_vocab_file(self) -> str:
        if self._vocab_json_path is None:
            raise RuntimeError("no vocab file configured for this fake model")
        return self._vocab_json_path

    def get_path_to_tokenizer_file(self) -> str:
        raise RuntimeError("fake model has no tokenizer_file fallback (test only uses vocab_file)")

    # -- test helpers ---------------------------------------------------------
    def write_vocab_json(self, path: Path) -> None:
        byte_level_vocab = {encode_bpe_token(text): idx for text, idx in self.text_to_id.items()}
        path.write_text(json.dumps(byte_level_vocab), encoding="utf-8")
        self._vocab_json_path = str(path)


@pytest.fixture
def all_pieces() -> list[str]:
    return _SINGLE_CHAR_PIECES + _MERGED_PIECES


@pytest.fixture
def make_model(tmp_path, all_pieces):
    def _make(text_bonus: dict[str, float] | None = None, dynamic_bonus=None) -> FakeSmallLLMModel:
        model = FakeSmallLLMModel(all_pieces, text_bonus=text_bonus, dynamic_bonus=dynamic_bonus)
        model.write_vocab_json(tmp_path / f"vocab_{id(model)}.json")
        return model

    return _make


def scripted_string_target(model: FakeSmallLLMModel, target: str):
    """Build a dynamic_bonus function that steers a JSONStringStep towards
    producing exactly `target`, then prefers the closing quote."""

    def _bonus(input_ids: list[int]) -> dict[str, float]:
        text = model.decode(input_ids)
        produced = 0
        for n in range(min(len(target), len(text)), -1, -1):
            if text.endswith(target[:n]):
                produced = n
                break
        if produced >= len(target):
            return {'"': 50.0}
        return {target[produced]: 50.0, '"': -50.0}

    return _bonus


def scripted_number_targets(model: FakeSmallLLMModel, marker_to_target: dict[str, str]):
    """Build a dynamic_bonus function for JSONNumberStep: once `marker` has
    appeared in the generated text, steer subsequent digits towards `target`."""

    def _bonus(input_ids: list[int]) -> dict[str, float]:
        text = model.decode(input_ids)
        active_marker = None
        for marker in marker_to_target:
            if marker in text:
                if active_marker is None or text.rindex(marker) > text.rindex(active_marker):
                    active_marker = marker
        if active_marker is None:
            return {}
        target = marker_to_target[active_marker]
        tail_after_marker = text.rsplit(active_marker, 1)[1]
        produced = ""
        for ch in tail_after_marker:
            if ch.isdigit() or ch in "-.":
                produced += ch
            else:
                produced = ""
        if produced == target:
            return {",": 50.0, "}": 50.0}
        if target.startswith(produced):
            next_char = target[len(produced)]
            return {next_char: 50.0}
        return {}

    return _bonus


@pytest.fixture
def make_vocabulary():
    def _make(model: FakeSmallLLMModel) -> Vocabulary:
        return Vocabulary.from_model(model)

    return _make
