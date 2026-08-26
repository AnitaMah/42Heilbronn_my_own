# ABOUTME: End-to-end smoke test: runs the real CLI against the real subject data files,
# ABOUTME: with llm_sdk swapped out for the in-memory fake model (no model download needed).

from __future__ import annotations

import json
import sys
import types
from pathlib import Path

from src.cli import main
from src.models import FunctionCallResult

REPO_ROOT = Path(__file__).resolve().parents[1]


def test_cli_end_to_end_against_real_subject_data(monkeypatch, make_model, tmp_path):
    model = make_model()
    # Growing pressure to close JSON strings guarantees termination regardless
    # of which characters the (untuned, in-memory) fake model happens to favor.
    model.dynamic_bonus = lambda input_ids: {'"': 0.2 * len(input_ids)}

    fake_module = types.ModuleType("llm_sdk")
    fake_module.Small_LLM_Model = lambda model_name=None: model  # type: ignore[attr-defined]
    monkeypatch.setitem(sys.modules, "llm_sdk", fake_module)

    output_path = tmp_path / "function_calling_results.json"
    exit_code = main(
        [
            "--functions_definition",
            str(REPO_ROOT / "data" / "input" / "functions_definition.json"),
            "--input",
            str(REPO_ROOT / "data" / "input" / "function_calling_tests.json"),
            "--output",
            str(output_path),
        ]
    )

    assert exit_code == 0
    payload = json.loads(output_path.read_text(encoding="utf-8"))

    functions = json.loads((REPO_ROOT / "data" / "input" / "functions_definition.json").read_text())
    prompts = json.loads((REPO_ROOT / "data" / "input" / "function_calling_tests.json").read_text())
    by_name = {fn["name"]: fn for fn in functions}

    assert len(payload) == len(prompts)
    for row in payload:
        result = FunctionCallResult.model_validate(row)  # exact 3-key shape, no extras
        assert result.name in by_name
        expected_keys = set(by_name[result.name]["parameters"].keys())
        assert set(result.parameters.keys()) == expected_keys
