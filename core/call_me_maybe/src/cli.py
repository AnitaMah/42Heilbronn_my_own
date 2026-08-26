# ABOUTME: Command-line entry point: argument parsing, wiring the model + vocabulary, and the
# ABOUTME: main per-prompt loop, with every failure mode turned into a clear stderr message.

"""``python -m src`` entry point.

Brief
-----
Wires everything else in this package together for a single run: parse CLI
flags, load and validate the two input files (`io_utils.py`), load the model
and build its vocabulary (`vocabulary.py`), resolve every prompt to a
function call (`function_caller.py`), and write the results
(`io_utils.write_results`). Every failure mode -- a missing file, a bad model
name, one prompt the grammar couldn't complete -- is caught here and turned
into a clear stderr message with a non-zero exit code rather than a raw
traceback, per the subject's "must never crash unexpectedly" rule.
"""

from __future__ import annotations

import argparse
import sys
import time

from .errors import CallMeMaybeError
from .function_caller import call_function_for_prompt
from .io_utils import load_function_definitions, load_test_prompts, write_results
from .models import FunctionCallResult
from .vocabulary import Vocabulary

DEFAULT_FUNCTIONS_FILE = "data/input/functions_definition.json"
DEFAULT_INPUT_FILE = "data/input/function_calling_tests.json"
DEFAULT_OUTPUT_FILE = "data/output/function_calling_results.json"
DEFAULT_MODEL_NAME = "Qwen/Qwen3-0.6B"


def build_arg_parser() -> argparse.ArgumentParser:
    """Construct the CLI's argument parser.

    ``--functions_definition`` accepts ``--function_definitions`` as an alias
    -- the subject itself uses both spellings in different places (see
    README.md's "Design decisions" section), so both are accepted rather than
    guessing which one a grader will actually pass.

    Returns
    -------
    argparse.ArgumentParser
        Configured parser; none of `--functions_definition`, `--input`,
        `--output`, or `--model` are required (each has a sensible default).
    """
    parser = argparse.ArgumentParser(
        prog="python -m src",
        description="Translate natural-language prompts into structured function calls "
        "using constrained decoding.",
    )
    parser.add_argument(
        "--functions_definition",
        "--function_definitions",
        dest="functions_definition",
        default=DEFAULT_FUNCTIONS_FILE,
        help=f"Path to the function definitions JSON file (default: {DEFAULT_FUNCTIONS_FILE}).",
    )
    parser.add_argument(
        "--input",
        dest="input_path",
        default=DEFAULT_INPUT_FILE,
        help=f"Path to the prompts JSON file (default: {DEFAULT_INPUT_FILE}).",
    )
    parser.add_argument(
        "--output",
        dest="output_path",
        default=DEFAULT_OUTPUT_FILE,
        help=f"Path to write the results JSON file (default: {DEFAULT_OUTPUT_FILE}).",
    )
    parser.add_argument(
        "--model",
        dest="model_name",
        default=DEFAULT_MODEL_NAME,
        help=f"Model identifier to load via llm_sdk (default: {DEFAULT_MODEL_NAME}).",
    )
    return parser


def main(argv: list[str] | None = None) -> int:
    """Run one end-to-end pass: load inputs, load the model, resolve every
    prompt, write the results.

    Parameters
    ----------
    argv : list[str] | None
        Argument vector to parse (defaults to `sys.argv[1:]` via argparse
        when `None`); overridable so tests can invoke `main()` directly
        instead of shelling out (see `tests/test_cli_smoke.py`).

    Returns
    -------
    int
        Process exit code: ``0`` on full or partial success (at least one
        prompt resolved), ``1`` if the input files couldn't be loaded, the
        model couldn't be loaded, the output couldn't be written, or *every*
        prompt failed to resolve.
    """
    args = build_arg_parser().parse_args(argv)

    # Load and validate both input files before touching the (expensive,
    # slow-to-load) model -- fail fast on bad input rather than downloading
    # gigabytes of model weights first.
    try:
        functions = load_function_definitions(args.functions_definition)
        prompts = load_test_prompts(args.input_path)
    except CallMeMaybeError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1

    try:
        from llm_sdk import Small_LLM_Model  # imported here so --help works with no model download
    except Exception as exc:  # noqa: BLE001
        print(f"error: could not import llm_sdk.Small_LLM_Model: {exc}", file=sys.stderr)
        return 1

    try:
        model = Small_LLM_Model(model_name=args.model_name)
        vocabulary = Vocabulary.from_model(model)
    except CallMeMaybeError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    except Exception as exc:  # noqa: BLE001
        print(f"error: could not load model {args.model_name!r}: {exc}", file=sys.stderr)
        return 1

    results: list[FunctionCallResult] = []
    failures = 0
    started = time.monotonic()

    # One bad prompt (a grammar that couldn't converge, an unexpected model
    # error) must never abort the whole batch -- log it and keep going.
    for item in prompts:
        try:
            result = call_function_for_prompt(model, vocabulary, item.prompt, functions)
            results.append(result)
        except CallMeMaybeError as exc:
            failures += 1
            print(f"warning: skipping prompt {item.prompt!r}: {exc}", file=sys.stderr)
        except Exception as exc:  # noqa: BLE001 - never let one bad prompt crash the run
            failures += 1
            print(f"warning: skipping prompt {item.prompt!r} (unexpected error): {exc}", file=sys.stderr)

    try:
        write_results(args.output_path, results)
    except CallMeMaybeError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1

    elapsed = time.monotonic() - started
    print(
        f"Processed {len(prompts)} prompt(s): {len(results)} succeeded, {failures} failed "
        f"in {elapsed:.1f}s. Output written to {args.output_path}"
    )
    return 0 if failures == 0 else (0 if results else 1)
