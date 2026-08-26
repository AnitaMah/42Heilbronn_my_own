# ABOUTME: "call me maybe" -- constrained-decoding function calling for small LLMs.

"""call me maybe: turns natural-language prompts into structured function
calls using constrained decoding, so a small model (Qwen/Qwen3-0.6B by
default) produces 100% valid, schema-compliant JSON on every call.

Brief / module map
-------------------
* `models.py`          -- pydantic schema for every JSON shape in play.
* `errors.py`           -- the exception hierarchy every module raises.
* `io_utils.py`         -- reading input files / writing the results file.
* `vocabulary.py`       -- model vocabulary loading + byte-level BPE (de)coding.
* `decoder.py`          -- low-level logit-masking primitives.
* `grammar.py`          -- the constrained-decoding grammar steps themselves.
* `function_caller.py`  -- per-prompt orchestration (name -> parameters).
* `cli.py` / `__main__.py` -- the ``python -m src`` entry point.

See README.md for the full write-up (algorithm explanation, design
decisions, and how to run it).
"""
