<i>This project has been created as part of the 42 curriculum by anmakhov.</i>

# call me maybe

## Description

`call me maybe` turns natural-language requests ("What is the sum of 2 and 3?") into
structured function calls (`{"name": "fn_add_numbers", "parameters": {"a": 2, "b": 3}}`)
using a small local LLM (`Qwen/Qwen3-0.6B` by default). The interesting constraint is that
small models are unreliable JSON generators when simply prompted for it — this project
does not rely on that. Instead it implements **constrained decoding**: at every generation
step, the model's logits are masked so that only tokens keeping the output both valid JSON
*and* compliant with the declared function schema can ever be chosen. The result is
guaranteed-parseable, schema-correct output regardless of how "confident" the model is.

## Instructions

```bash
make install   # uv sync — installs numpy, pydantic, and llm_sdk (which pulls in torch/transformers)
make run       # uv run python -m src, reads data/input/, writes data/output/
make debug     # same, under pdb
make lint      # flake8 + mypy (mandatory flags)
make lint-strict
make test      # pytest — the unit/integration suite (not graded, but real and green)
make clean
```

Full CLI form:

```bash
uv run python -m src \
  --functions_definition data/input/functions_definition.json \
  --input data/input/function_calling_tests.json \
  --output data/output/function_calling_results.json
```

All three flags are optional and default to the paths above. `--model` overrides the model
id if you want to try something other than the default.

## Algorithm explanation

Generation is driven by a small grammar built once per prompt from the chosen function's
schema, walked step by step (`src/grammar.py`, orchestrated by `src/function_caller.py`):

1. **Literal steps** emit fixed structural text (`{"name": "`, `", "parameters": {`, `}}`,
   the `"key": ` for each parameter). No model choice is involved — the tokens are just fed
   into the model so it keeps seeing consistent context.
2. **Enum steps** force the model to spell out one of a fixed set of strings — used for the
   function name (the enum of declared function names) and for JSON booleans (`true`/`false`).
   At every token, the candidate set is every vocabulary token that keeps the text-so-far a
   prefix of *at least one* remaining option; everything else is masked to `-inf`.
3. **String steps** generate the body of a JSON string one token at a time. Any token
   containing an unescaped quote, backslash, or raw control character is masked out; the
   step ends the moment the model picks the literal `"` token. (Known simplification:
   generated strings can't themselves contain a literal backslash or embedded quote — more
   than enough for this project's functions; see "Design decisions" below.)
4. **Number steps** are the interesting case, because JSON numbers have no closing
   delimiter. The grammar tracks a strict prefix/complete distinction per RFC 8259 (sign,
   *mandatory* integer part, optional fraction, optional exponent — in that order); once the
   digits generated so far already form a complete number, generation stops as soon as the
   model's own *unconstrained* top preference would leave the number grammar anyway (i.e.
   it naturally wants to move on to `,`/`}`/whitespace). This lets the model decide *how
   many digits*, without ever letting it emit something structurally invalid while deciding.

The vocabulary itself (`src/vocabulary.py`) is read from whatever file `llm_sdk` exposes
(`get_path_to_vocab_file()`, or `get_path_to_tokenizer_file()` as a fallback) and decoded by
hand-implementing the standard GPT-2/Qwen byte-level BPE alphabet — deliberately not via
`transformers`, since importing it directly in `src/` is against the subject's rules.

## Design decisions

- **pydantic everywhere required by the subject** (`src/models.py`): function definitions,
  prompts, and results are all pydantic models with `extra="forbid"`, so a malformed input
  file fails fast with a specific validation error instead of silently producing garbage.
- **Deterministic (argmax) selection**, not sampling. Given the reliability bar (90%+
  accuracy, 100% valid JSON), greedy masked-argmax is simpler to reason about and to test
  than temperature sampling, at the cost of some diversity we don't need here.
- **String grammar simplification**: bodies may not contain a raw backslash or embedded
  quote. A fully general JSON string grammar needs proper escape-sequence handling across
  token boundaries (a token can end mid-escape); the functions in this project's schema
  never need that, so the simpler, fully-correct-for-this-domain rule was chosen over a more
  complex parser that would be hard to verify.
- **The "let the model tell us when a number is done" heuristic** (see above) avoids the
  alternative of hand-rolling a lookahead into the following literal token, which would
  couple the number grammar to whatever comes after it in the JSON structure.
- **CLI accepts both `--functions_definition` and `--function_definitions`** — the subject
  itself uses both spellings in different places (Chapter IV's usage example vs. Chapter
  V.2), so both are accepted rather than picking one and hoping the grader agrees.

## Performance analysis

Structural guarantees (verified by the test suite, see below) are unconditional:

- **100% valid JSON / schema-compliant output** — enforced by construction. Every literal
  and value step masks logits before a choice is made, so a call to `call_function_for_prompt`
  can only ever return a `FunctionCallResult` with the exact three keys, the right function
  name, and the right argument types. `tests/test_function_caller.py::test_output_is_always_schema_valid_regardless_of_model_preference`
  fuzzes this across 8 randomized (adversarial-ish) logit preferences and asserts it holds
  every time.
- **Speed**: the current implementation scans the full vocabulary (~150k tokens for Qwen3)
  on every generation step, which is the honest, simple baseline — not the fastest possible.
  For a ~150k-token vocab this is the main place to optimize further if `make run` turns out
  too slow on real hardware: precompute the token-id candidate set once per grammar *state*
  (e.g. all tokens valid as "still building a JSON number") instead of re-filtering the whole
  vocabulary every step, and/or build a prefix trie over vocabulary token strings for the
  enum/string steps so candidate lookup is O(matches) instead of O(vocab size).
- **Accuracy** (does it pick the *right* function and the *right* argument values) depends
  on the underlying model's actual language understanding, which this project does not
  control — constrained decoding guarantees the output is well-formed, not that it's
  semantically correct. That has to be measured by actually running `Qwen/Qwen3-0.6B`
  against the real test prompts.

## Challenges faced

- **This sandbox has no route to huggingface.co** (network egress is allow-listed and does
  not include it), so `Small_LLM_Model` cannot actually download `Qwen/Qwen3-0.6B` here —
  `uv run python -m src` fails cleanly with `error: could not load model 'Qwen/Qwen3-0.6B': ...`
  (exit code 1, no traceback), which is the correct graceful-failure behavior, but it means
  the full pipeline could not be run end-to-end against the *real* model in this environment.
  `uv sync` itself does succeed here (confirmed: pulls in torch/transformers/huggingface-hub
  cleanly), so this should just work on a machine with normal internet access.
- **A real bug the test suite caught**: the first version of the JSON-number prefix grammar
  allowed an *omitted* integer part once a `.` had been produced (i.e. it treated `"-."` as
  a valid partial number). With a neutral, no-preference model that's exactly the state the
  decoder wandered into, appending `.000...` forever until it hit the safety cap and raised
  `GenerationError`. `tests/test_grammar.py::test_json_number_step_never_gets_stuck_with_no_preference`
  and the CLI smoke test (below) both caught this before it could reach the real model; the
  fix makes the integer part mandatory in every prefix pattern, matching RFC 8259.
- **No official grader for this project was found.** `for work/moulinette.zip` in the
  project folder is a real moulinette binary, but its subcommands
  (`evaluate_student_search_results`, `list_valid_questions`, `evaluate_student_answers`)
  are for the "RAG against the machine" subject, not this one — it has no notion of function
  calls or JSON schema validation. There does not appear to be a moulinette specific to
  `call me maybe` in this folder, so validation here relies on the test suite plus manual
  review against the subject's own validation rules (Chapter V.4.2).

## Testing strategy

`make test` runs 25 pytest tests against an in-memory `FakeSmallLLMModel` (implements the
same interface as `llm_sdk.Small_LLM_Model` — `encode`/`decode`/`get_logits_from_input_ids`/
`get_path_to_vocab_file`) so the constrained-decoding logic is fully exercised without
needing model weights or network access:

- `test_vocabulary.py` — the hand-rolled byte-level BPE encode/decode round-trips correctly.
- `test_io_utils.py` — missing files, malformed JSON, and schema mismatches all raise the
  right typed error instead of crashing; valid files round-trip through write/read.
- `test_grammar.py` — each grammar step in isolation: enum steps never escape their option
  set (even when bribed with a huge logit bonus for a character outside it); string steps
  never embed a raw quote; number steps handle zero, negatives, decimals, and — the
  regression test — never get stuck with a neutral model.
- `test_function_caller.py` — end-to-end per-prompt generation with a *scripted* fake model
  (steers logits based on what's already been generated, e.g. "the `a` parameter is filled
  in with `2` now, so prefer `3` next") to prove specific target outputs are reachable, plus
  an 8-trial fuzz test with randomized logit preferences asserting the output is always
  schema-valid regardless.
- `test_cli_smoke.py` — runs the actual `src.cli.main()` entry point against the *real*
  `data/input/functions_definition.json` and `function_calling_tests.json` shipped with the
  subject, with `llm_sdk` swapped out for the fake model via `sys.modules` patching. This is
  what caught the number-grammar bug above.

## Example usage

```bash
$ make run
Processed 11 prompt(s): <succeeded> succeeded, <failed> failed in <elapsed>s. Output written to data/output/function_calling_results.json
```

Each line of `data/output/function_calling_results.json` has this shape (this specific
`fn_add_numbers` example was hand-traced through the grammar in `src/function_caller.py`
and `tests/test_function_caller.py::test_end_to_end_picks_add_numbers_with_two_arguments`
using the fake test model, not a real run of `Qwen/Qwen3-0.6B` — see "Challenges faced" for
why a real run wasn't possible in the environment this project was built in):

```json
{
  "prompt": "What is the sum of 2 and 3?",
  "name": "fn_add_numbers",
  "parameters": {"a": 2, "b": 3}
}
```

Fill in the real console output and any interesting example rows here once `make run` has
been executed against the actual model on a machine with network access.

## Resources

- [RFC 8259 — The JSON Data Interchange Format](https://www.rfc-editor.org/rfc/rfc8259)
  (the number/string grammar `src/grammar.py` implements directly).
- [Language Models are Unsupervised Multitask Learners (GPT-2 paper)](https://cdn.openai.com/better-language-models/language_models_are_unsupervised_multitask_learners.pdf) —
  origin of the byte-level BPE alphabet reimplemented in `src/vocabulary.py`.
- [Qwen3 technical report](https://arxiv.org/abs/2505.09388) — background on the default model.
- Hugging Face's [guidance on structured generation / constrained decoding](https://huggingface.co/docs)
  and the [`outlines`](https://github.com/dottxt-ai/outlines) library's public writeups on
  finite-state-machine-guided decoding, for the general technique (not used as a dependency —
  it's explicitly forbidden by this subject — but useful background reading).

**AI usage disclosure**: this project (grammar design, all of `src/`, the test suite, and
this README) was built with Claude (Anthropic) as a hands-on pair-programming collaborator
in a Claude Code / Cowork session, working from the subject PDF and the real
`function_definitions.json`/`function_calling_tests.json`/`llm_sdk` files. Claude wrote the
constrained-decoding grammar, the vocabulary/BPE handling, the CLI/IO layer, and the pytest
suite (including the fake-model test harness), and iterated on the test failures it produced
(including finding and fixing the JSON-number grammar bug documented above). Before
submitting or defending this project, its author reviewed and understood every module well
enough to explain the design during evaluation, per the subject's AI-usage rules (Chapter II).
