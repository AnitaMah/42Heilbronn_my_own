# python09 — Cosmic Data (Pydantic) — Implementation Plan

Source: `python09.pdf` v3.0. Broken into small steps — each one should be a
few minutes of work, something you can test in isolation before moving to
the next. Nothing here is a drop-in solution; write and run each step
yourself so you can defend it.

## Step 0 — Environment

1. `python3 --version` → confirm 3.10+
2. `python3 -m venv venv`
3. Activate the venv
4. `pip install pydantic flake8 mypy`
5. `python -c "import pydantic; print(pydantic.VERSION)"` → confirm it
   starts with `2.`
6. Create empty dirs: `python09/ex0/`, `python09/ex1/`, `python09/ex2/`
7. Copy `data_generator.py` and `data_exporter.py` into
   `python09/tools/`
8. Run `data_generator.py` (or `data_exporter.py`) once, look inside
   `generated_data/` — open the JSON for stations, contacts, and missions
   and skim a few records so you know what real input looks like

## Step 1 — ex0: `SpaceStation` model, no logic yet

1. Create `ex0/space_station.py`, import `BaseModel`, `Field` from
   `pydantic`, and `datetime` from `datetime`
2. Add the class shell: `class SpaceStation(BaseModel):` with nothing in
   it but `pass`, confirm it imports with no errors
3. Add `station_id: str = Field(..., min_length=3, max_length=10)` —
   nothing else yet
4. In a scratch `if __name__ == "__main__":` block, instantiate
   `SpaceStation(station_id="ISS001")` and print it — confirm it works
   before adding the next field
5. Add `name: str` with its length constraint, re-test
6. Add `crew_size: int` with `ge=1, le=20`, re-test
7. Add `power_level: float` with `ge=0.0, le=100.0`, re-test
8. Add `oxygen_level: float` with the same bounds, re-test
9. Add `last_maintenance: datetime` (no constraint needed) — test it by
   passing a plain ISO string like `"2024-01-01T00:00:00"` and printing
   the resulting field's `type()` to see Pydantic's auto-conversion
10. Add `is_operational: bool = True`, re-test with and without passing it
11. Add `notes: str | None = Field(default=None, max_length=200)`,
    re-test with and without it
12. Delete the scratch test code from step 4–11 once every field works —
    you'll replace it with a real `main()` next

## Step 2 — ex0: `main()` and error handling

1. Write `def main() -> None:` with a docstring
2. Inside it, build one valid `SpaceStation` with realistic values
3. Print a header line (`"Space Station Data Validation"`) and a
   `"="*N` divider, matching the PDF's example
4. Print each field of the valid station on its own line
5. Wrap a *second*, deliberately invalid construction (e.g.
   `crew_size=25`) in `try: / except ValidationError as e:`
6. Print a divider and `"Expected validation error:"` then the error
   detail — for now just `print(e)`, then look at the raw output and
   decide if you want to extract just the message text
7. Add `if __name__ == "__main__": main()` at the bottom
8. Run the file directly, confirm the output matches the PDF's expected
   layout

## Step 3 — ex0: test against real + broken data

1. Load one station record from `generated_data/stations.json` by hand
   and construct a `SpaceStation` from it — confirm it validates
2. Pick one field, break it on purpose (e.g. set `oxygen_level=150`),
   confirm the error message names that field
3. Repeat step 2 for at least two more fields you haven't tested yet
4. Run `flake8 ex0/space_station.py`, fix anything it flags
5. Run `mypy ex0/space_station.py`, fix anything it flags

## Step 4 — ex1: `ContactType` enum + bare model

1. Create `ex1/alien_contact.py`, import `BaseModel`, `Field`,
   `model_validator` from `pydantic`, `Enum` from `enum`, `datetime`
2. Define `class ContactType(str, Enum):` with `RADIO = "radio"`,
   `VISUAL = "visual"`, `PHYSICAL = "physical"`,
   `TELEPATHIC = "telepathic"`
3. Add `class AlienContact(BaseModel):` shell
4. Add `contact_id: str` (5–15 chars), test-instantiate with just this
   field plus placeholders
5. Add `timestamp: datetime`
6. Add `location: str` (3–100 chars)
7. Add `contact_type: ContactType` — test passing both the string
   `"radio"` and `ContactType.RADIO` to see both work
8. Add `signal_strength: float` (0.0–10.0)
9. Add `duration_minutes: int` (1–1440)
10. Add `witness_count: int` (1–100)
11. Add `message_received: str | None` (optional, max 500 chars)
12. Add `is_verified: bool = False`
13. Build one full valid instance and print it — confirm every field
    round-trips correctly before adding any custom validation

## Step 5 — ex1: custom validation rules, one at a time

1. Add an empty validator:
   ```
   @model_validator(mode="after")
   def check_business_rules(self) -> "AlienContact":
       return self
   ```
   confirm the model still builds with it in place
2. Add rule 1 only: `contact_id` must start with `"AC"` — raise
   `ValueError("...")` if not. Test with a passing and a failing id
3. Add rule 2 only: if `contact_type is ContactType.PHYSICAL` then
   `is_verified` must be `True`. Test both branches
4. Add rule 3 only: if `contact_type is ContactType.TELEPATHIC` then
   `witness_count >= 3`. Test both branches
5. Add rule 4 only: if `signal_strength > 7.0` then `message_received`
   must be set — decide here whether "should" means you raise or just
   log, and write a one-line comment explaining your choice
6. Re-run all four tests from steps 2–5 together on one script to make
   sure an earlier rule isn't silently masking a later one

## Step 6 — ex1: `main()` and cleanup

1. Write `main() -> None` following the same two-block layout as ex0
   (valid report printed, divider, one failing case with its error)
2. Pick the failing case to be the telepathic/witness-count rule, to
   match the PDF's expected output
3. Add `if __name__ == "__main__": main()`
4. Test against a real record from `generated_data/alien_contacts.json`
5. `flake8 ex1/alien_contact.py`, fix flags
6. `mypy ex1/alien_contact.py`, fix flags

## Step 7 — ex2: `Rank` enum + `CrewMember`, standalone

1. Create `ex2/space_crew.py`, same imports as ex1 plus nothing new yet
2. Define `class Rank(str, Enum):` with `CADET`, `OFFICER`,
   `LIEUTENANT`, `CAPTAIN`, `COMMANDER`
3. Build `class CrewMember(BaseModel):` field by field, testing after
   each one exactly like Step 1: `member_id` (3–10), `name` (2–50),
   `rank` (Rank), `age` (18–80), `specialization` (3–30),
   `years_experience` (0–50), `is_active: bool = True`
4. Once all fields are in, build 2–3 standalone `CrewMember` instances
   and print them — don't touch `SpaceMission` yet

## Step 8 — ex2: `SpaceMission` with a plain crew list

1. Add `class SpaceMission(BaseModel):` shell
2. Add `mission_id` (5–15), `mission_name` (3–100), `destination`
   (3–50), `launch_date: datetime`, `duration_days` (1–3650), one field
   at a time as before
3. Add `crew: list[CrewMember] = Field(..., min_length=1, max_length=12)`
   — build a `SpaceMission` using the `CrewMember` instances from Step 7
   and print `mission.crew[0].name` to confirm nesting works
4. Deliberately pass one broken `CrewMember` dict inside the crew list
   (e.g. `age=5`) and read the raised `ValidationError` — note how it
   points at `crew.<index>.<field>`
5. Add `mission_status: str = "planned"`
6. Add `budget_millions: float` (1.0–10000.0)

## Step 9 — ex2: mission-level validation rules, one at a time

1. Add the empty `@model_validator(mode="after")` shell, confirm it still
   builds
2. Add rule 1: `mission_id` must start with `"M"`. Test both branches
3. Add rule 2: `crew` must contain at least one `commander` or `captain`
   — write it as
   `any(m.rank in (Rank.COMMANDER, Rank.CAPTAIN) for m in self.crew)`.
   Test both branches
4. Add rule 3: if `duration_days > 365`, at least 50% of crew must have
   `years_experience >= 5` — write the ratio with
   `sum(1 for m in self.crew if m.years_experience >= 5) / len(self.crew)`.
   Test with exactly 50%, just under, and just over
5. Add rule 4: every crew member must have `is_active == True` — use
   `all(m.is_active for m in self.crew)`. Test both branches
6. Run all four rules together on one mission that should pass and one
   that should fail each rule individually (four failing cases total)

## Step 10 — ex2: `main()` and cleanup

1. Write `main() -> None`: one valid mission with 2–3 crew members,
   printed with a per-member list line like the PDF's example
2. One invalid mission (missing commander/captain, matching the PDF's
   expected error), error printed
3. Add `if __name__ == "__main__": main()`
4. Test against a real record from `generated_data/space_missions.json`
5. `flake8 ex2/space_crew.py`, fix flags
6. `mypy ex2/space_crew.py`, fix flags

## Step 11 — final pass

1. Re-read all three files top to bottom — check docstrings and comments
   explain *why* a rule exists, not just what it does
2. Confirm no deprecated `@validator` anywhere, only `@model_validator`
3. Confirm every function signature (including `main`) has full type
   annotations
4. Confirm only `space_station.py`, `alien_contact.py`, `space_crew.py`
   are what you intend to submit — no scratch/test files in the repo
5. `git add` / `git commit` each exercise separately (ex0, then ex1, then
   ex2) so the history shows incremental progress
6. Push to your assigned repo

## A note on AI here (per the subject's own Ch. II)

Asking "how do I express a cross-field rule in `model_validator`" is fine.
Pasting a generated `alien_contact.py` wholesale is not — you need to
explain, live, why each rule works the way it does, and generated code you
didn't reason through is exactly the failure mode the PDF warns about on
p.4.
