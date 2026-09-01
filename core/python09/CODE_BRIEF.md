# python09 — Code Brief (for your defense/peer review)

What each file does and why, so you can explain it without re-deriving it
live. Read this alongside the actual code, not instead of it.

## ex0/space_station.py

**What it is:** a plain `BaseModel` with eight `Field`-constrained
attributes, no custom logic — this exercise is entirely about the
built-in constraint system.

**Field choices, one line each:**
- `station_id`, `name`: `str` with `min_length`/`max_length` — Pydantic
  checks length after coercing to `str`, so a non-string input (e.g. an
  int) fails type validation before length is even checked
- `crew_size`, `oxygen_level`, `power_level`: numeric bounds via `ge=`/
  `le=` (inclusive) — matches the PDF's "1-20" / "0.0-100.0" wording,
  which reads as inclusive on both ends
- `last_maintenance: datetime` — no explicit constraint; Pydantic parses
  ISO-8601 strings into real `datetime` objects automatically. That's
  the "auto type conversion" the PDF's pro-tip is pointing at
- `notes: Optional[str]` with `default=None` — the only field where
  absence is valid, per the spec calling it "Optional"

**`main()` structure:** builds one valid station, prints it in a labeled
block, then wraps a second (deliberately invalid, `crew_size=25`)
construction in `try/except ValidationError`, printing
`error.errors()[0]["msg"]`. That's the "protect the data stream from
corruption" requirement in practice — an uncaught `ValidationError` would
crash the program on the first bad record.

**Nothing to defend here beyond**: why each bound is inclusive (`ge`/`le`
vs `gt`/`lt`) — because the subject's ranges are written as closed
intervals ("1-20 people", not "1 up to but not including 20").

## ex1/alien_contact.py

**What it is:** the same field-constraint layer as ex0, plus one
`@model_validator(mode="after")` enforcing four rules that no single
field can check on its own — that's the whole point of "after" mode:
it runs once every individual field has already passed its own
validation, so inside the validator you can trust `self.contact_type` is
really a `ContactType`, `self.witness_count` is really an `int`, etc.

**The four rules, and why each is written the way it is:**
1. `contact_id` must start with `"AC"` — a naming-convention check on a
   plain string field, string method, nothing subtle
2. physical contact requires `is_verified=True` — reads the two fields
   together; can't be expressed as a `Field(...)` constraint because it
   depends on *another* field's value
3. telepathic contact requires `witness_count >= 3` — same shape as
   rule 2, different fields
4. **the judgment call**: "strong signals (>7.0) should include received
   messages." Every other rule says "must" — this one says "should." I
   read it as a hard requirement anyway (raises `ValueError` like the
   others) rather than a soft warning, and set the boundary at strictly
   `> 7.0` so a signal of exactly `7.0` does *not* require a message.
   **Be ready to justify this reading** — it's the one place the subject
   is genuinely ambiguous, and a peer reviewer may push on it.

**The `_clean_error_message` helper:** Pydantic wraps any `ValueError`
you raise inside a validator as `"Value error, <your message>"` in the
error dict. This helper strips that prefix so the printed output matches
the PDF's plain-text expected output. Worth knowing this exists and why
— it's easy to miss if you only look at `error.errors()[0]["msg"]`
directly and wonder why there's an extra "Value error," in front.

## ex2/space_crew.py

**What it is:** two models, not one — `CrewMember` (flat, same style as
ex0/ex1) nested inside `SpaceMission` via `crew: List[CrewMember]`, plus
a `@model_validator` on `SpaceMission` whose four rules all reason about
the *list* of crew members, not just scalar fields.

**Why nesting matters here (the concept this exercise is testing):**
when you build a `SpaceMission`, Pydantic validates every `CrewMember` in
the `crew` list *first* — each one independently, against `CrewMember`'s
own field constraints — before `SpaceMission`'s own fields are finalized
and before the mission-level `@model_validator` ever runs. So a bad crew
member (e.g. `age=200`) never even reaches your mission-level rules; it
fails immediately with an error location like `('crew', 0, 'age')`
pointing at exactly which list index and field broke. That ordering is
worth being able to state explicitly if asked "what happens when a
CrewMember fails inside a SpaceMission?"

**The four mission-level rules:**
1. `mission_id` starts with `"M"` — same shape as ex1's rule 1
2. at least one `Rank.COMMANDER` or `Rank.CAPTAIN` in the crew — written
   with `any(... for member in self.crew)`, a comprehension over the
   nested list rather than a manual loop with a flag variable
3. **the other judgment call**: missions longer than 365 days need at
   least 50% of crew with `years_experience >= 5`. I computed the ratio
   as `experienced / len(self.crew)` and used `< 0.5` to fail — meaning
   *exactly* 50% experienced **passes**. The subject says "at least
   50%," which supports this reading, but it's still a boundary decision
   you should be able to state out loud
4. every crew member must be `is_active` — `all(... for member in
   self.crew)`, same comprehension pattern as rule 2

**Why comprehensions instead of loops:** rules 2 and 4 are existence/
universality checks (`any`/`all`) over the crew list — that's exactly
what those built-ins are for, and it reads more clearly in a defense
than a hand-rolled loop with a boolean flag you toggle and check after.

## Cross-file pattern worth naming if asked

All three files follow the same shape: `BaseModel` subclass(es) for
structure and simple constraints, one `@model_validator(mode="after")`
per model for anything that needs to see more than one field at once,
and a `main()` that always shows one valid case and one that fails a
*specific, named* rule rather than a generic invalid case — matching the
PDF's own expected-output examples. If you're asked "why after and not
before," the answer is: `mode="before"` runs on raw, not-yet-validated
input (still could be the wrong type entirely), which is the wrong place
for rules like "physical contact must be verified" that only make sense
once you already know `contact_type` is genuinely a `ContactType`.
