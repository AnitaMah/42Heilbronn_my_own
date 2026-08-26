import json

import pytest

from src.errors import InputFileError, SchemaValidationError
from src.io_utils import load_function_definitions, load_test_prompts, write_results
from src.models import FunctionCallResult


def test_missing_file_raises_input_file_error(tmp_path):
    with pytest.raises(InputFileError):
        load_function_definitions(tmp_path / "does_not_exist.json")


def test_malformed_json_raises_input_file_error(tmp_path):
    path = tmp_path / "broken.json"
    path.write_text("{not: valid json,,,", encoding="utf-8")
    with pytest.raises(InputFileError):
        load_test_prompts(path)


def test_wrong_top_level_type_raises_schema_error(tmp_path):
    path = tmp_path / "bad_shape.json"
    path.write_text(json.dumps({"prompt": "not an array"}), encoding="utf-8")
    with pytest.raises(SchemaValidationError):
        load_test_prompts(path)


def test_duplicate_function_names_rejected(tmp_path):
    path = tmp_path / "functions.json"
    path.write_text(
        json.dumps(
            [
                {"name": "fn_a", "description": "", "parameters": {}, "returns": {"type": "number"}},
                {"name": "fn_a", "description": "", "parameters": {}, "returns": {"type": "number"}},
            ]
        ),
        encoding="utf-8",
    )
    with pytest.raises(SchemaValidationError):
        load_function_definitions(path)


def test_valid_function_definitions_load(tmp_path):
    path = tmp_path / "functions.json"
    path.write_text(
        json.dumps(
            [
                {
                    "name": "fn_add_numbers",
                    "description": "Add two numbers.",
                    "parameters": {"a": {"type": "number"}, "b": {"type": "number"}},
                    "returns": {"type": "number"},
                }
            ]
        ),
        encoding="utf-8",
    )
    functions = load_function_definitions(path)
    assert functions[0].name == "fn_add_numbers"
    assert list(functions[0].parameters.keys()) == ["a", "b"]


def test_write_results_round_trips(tmp_path):
    out_path = tmp_path / "nested" / "results.json"
    results = [FunctionCallResult(prompt="hi", name="fn_greet", parameters={"name": "shrek"})]
    write_results(out_path, results)
    loaded = json.loads(out_path.read_text(encoding="utf-8"))
    assert loaded == [{"prompt": "hi", "name": "fn_greet", "parameters": {"name": "shrek"}}]
