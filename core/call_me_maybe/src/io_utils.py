# ABOUTME: Reading and writing the project's JSON input/output files with graceful error handling.
# ABOUTME: Every file operation here is wrapped so a missing or malformed file becomes a clear
# ABOUTME: InputFileError instead of an unhandled crash.

"""File I/O boundary between the filesystem and the rest of the project.

Brief
-----
Everything that touches a path on disk lives in this one module: reading the
two input JSON files (with validation against the pydantic models in
`models.py`) and writing the final results file. Keeping I/O in one place
means every other module works with already-validated Python objects and
never has to think about missing files, permissions, or malformed JSON.
"""

from __future__ import annotations

import json
from pathlib import Path
from typing import Any

from pydantic import ValidationError

from .errors import InputFileError, SchemaValidationError
from .models import FunctionCallResult, FunctionDefinition, TestPrompt


def _read_json(path: str | Path) -> Any:
    """Read and parse one JSON file, translating every failure mode the
    subject calls out (missing file, unreadable file, malformed JSON) into a
    single, clearly-worded :class:`InputFileError`.

    Parameters
    ----------
    path : str | Path
        Path to the JSON file to read.

    Returns
    -------
    Any
        Whatever `json.load` returns -- callers are responsible for checking
        the shape (list vs. dict, etc.) before treating it as trusted data.
    """
    file_path = Path(path)
    try:
        with file_path.open("r", encoding="utf-8") as handle:
            return json.load(handle)
    except FileNotFoundError as exc:
        raise InputFileError(f"Input file not found: {file_path}") from exc
    except PermissionError as exc:
        raise InputFileError(f"Cannot read input file (permission denied): {file_path}") from exc
    except json.JSONDecodeError as exc:
        raise InputFileError(
            f"Input file is not valid JSON: {file_path} (line {exc.lineno}, column {exc.colno}: {exc.msg})"
        ) from exc
    except OSError as exc:
        raise InputFileError(f"Could not read input file {file_path}: {exc}") from exc


def load_function_definitions(path: str | Path) -> list[FunctionDefinition]:
    """Load and validate ``function_definitions.json``.

    Parameters
    ----------
    path : str | Path
        Path to the function-definitions JSON file.

    Returns
    -------
    list[FunctionDefinition]
        One validated model per declared function, in file order (order
        matters: the constrained decoder walks each function's parameters in
        the order they were declared).

    Raises
    ------
    SchemaValidationError
        If the file isn't a JSON array, a definition fails pydantic
        validation, the array is empty, or two functions share a name (the
        enum step in `grammar.py` assumes names are unique).
    """
    raw = _read_json(path)
    if not isinstance(raw, list):
        raise SchemaValidationError(
            f"{path}: expected a JSON array of function definitions, got {type(raw).__name__}"
        )
    try:
        definitions = [FunctionDefinition.model_validate(item) for item in raw]
    except ValidationError as exc:
        raise SchemaValidationError(f"{path}: invalid function definition(s):\n{exc}") from exc

    if not definitions:
        raise SchemaValidationError(f"{path}: no function definitions found")

    # Duplicate names would make the function-name enum step ambiguous (two
    # different schemas reachable from the same literal string), so reject
    # that up front rather than letting it surface as a confusing bug later.
    names = [d.name for d in definitions]
    duplicates = {n for n in names if names.count(n) > 1}
    if duplicates:
        raise SchemaValidationError(f"{path}: duplicate function name(s): {sorted(duplicates)}")

    return definitions


def load_test_prompts(path: str | Path) -> list[TestPrompt]:
    """Load and validate ``function_calling_tests.json``.

    Parameters
    ----------
    path : str | Path
        Path to the prompts JSON file.

    Returns
    -------
    list[TestPrompt]
        One validated model per prompt, in file order.

    Raises
    ------
    SchemaValidationError
        If the file isn't a JSON array, an entry fails pydantic validation,
        or the array is empty.
    """
    raw = _read_json(path)
    if not isinstance(raw, list):
        raise SchemaValidationError(
            f"{path}: expected a JSON array of prompts, got {type(raw).__name__}"
        )
    try:
        prompts = [TestPrompt.model_validate(item) for item in raw]
    except ValidationError as exc:
        raise SchemaValidationError(f"{path}: invalid prompt entr(y/ies):\n{exc}") from exc

    if not prompts:
        raise SchemaValidationError(f"{path}: no prompts found")

    return prompts


def write_results(path: str | Path, results: list[FunctionCallResult]) -> None:
    """Write the final output file, creating parent directories as needed.

    Parameters
    ----------
    path : str | Path
        Destination path for the results JSON file (e.g.
        ``data/output/function_calling_results.json``).
    results : list[FunctionCallResult]
        The resolved function calls to serialize, in the order they should
        appear in the output array.

    Raises
    ------
    InputFileError
        If the parent directory can't be created or the file can't be
        written (e.g. permission denied, disk full).
    """
    file_path = Path(path)
    try:
        file_path.parent.mkdir(parents=True, exist_ok=True)
        # model_dump() gives exactly the three required keys (prompt, name,
        # parameters) in that order, matching the subject's output schema.
        payload = [r.model_dump() for r in results]
        with file_path.open("w", encoding="utf-8") as handle:
            json.dump(payload, handle, indent=2, ensure_ascii=False)
            handle.write("\n")
    except OSError as exc:
        raise InputFileError(f"Could not write output file {file_path}: {exc}") from exc
