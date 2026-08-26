import json

import pytest

from src.errors import GenerationError
from src.grammar import EnumStep, JSONBooleanStep, JSONNumberStep, JSONStringStep, LiteralStep
from conftest import scripted_string_target


def test_literal_step_is_deterministic(make_model, make_vocabulary):
    model = make_model()
    vocabulary = make_vocabulary(model)
    text, ids = LiteralStep('{"name": "').run(model, vocabulary, [])
    assert text == '{"name": "'
    assert model.decode(ids) == '{"name": "'


def test_enum_step_picks_the_model_preferred_option(make_model, make_vocabulary):
    # both options share the "fn_" prefix and diverge afterwards -- the decoder
    # must follow the *masked* preference at the divergence point, not just
    # take the highest-logit token globally.
    model = make_model(text_bonus={"g": 50.0, "reverse": -50.0})
    vocabulary = make_vocabulary(model)
    text, ids = EnumStep(["fn_greet", "fn_reverse_string"]).run(model, vocabulary, [])
    assert text == "fn_greet"


def test_enum_step_never_escapes_the_option_set(make_model, make_vocabulary):
    # even with a huge bonus on a character that isn't part of any option, the
    # decoder must never wander off the enum.
    model = make_model(text_bonus={"z": 1000.0})
    vocabulary = make_vocabulary(model)
    text, _ = EnumStep(["fn_add_numbers", "fn_greet"]).run(model, vocabulary, [])
    assert text in {"fn_add_numbers", "fn_greet"}


def test_enum_step_raises_on_empty_options(make_model, make_vocabulary):
    model = make_model()
    vocabulary = make_vocabulary(model)
    with pytest.raises(GenerationError):
        EnumStep([]).run(model, vocabulary, [])


def test_json_boolean_step(make_model, make_vocabulary):
    model = make_model(text_bonus={"false": 10.0})
    vocabulary = make_vocabulary(model)
    text, _ = JSONBooleanStep().run(model, vocabulary, [])
    assert text == "false"


def test_json_string_step_produces_valid_string(make_model, make_vocabulary):
    model = make_model()
    model.dynamic_bonus = scripted_string_target(model, "shrek")
    vocabulary = make_vocabulary(model)
    body, ids = JSONStringStep().run(model, vocabulary, [])
    assert body == "shrek"
    # what the model actually saw fed into it must be `"<body>"` -- valid JSON on its own
    full = model.decode(ids)
    assert full == json.dumps(body)
    json.loads(full)  # must not raise


def test_json_string_step_never_embeds_a_raw_quote_even_with_bonus(make_model, make_vocabulary):
    # try to bribe the model into putting a quote mid-string; masking must stop it
    # from ever choosing '"' except as the terminator.
    model = make_model(text_bonus={'"': 1000.0, "a": 1.0})
    vocabulary = make_vocabulary(model)
    body, ids = JSONStringStep().run(model, vocabulary, [])
    full = model.decode(ids)
    json.loads(full)  # still valid JSON
    assert body.count('"') == 0


def test_json_number_step_generates_multi_digit_number(make_model, make_vocabulary):
    model = make_model(text_bonus={"2": 10.0, "6": 10.0, "5": 10.0, ".": -50.0, "-": -50.0})
    vocabulary = make_vocabulary(model)
    text, ids = JSONNumberStep().run(model, vocabulary, [])
    assert text != ""
    json.loads(text)  # must parse as a JSON number on its own
    full = model.decode(ids)
    assert full == text


def test_json_number_step_handles_negative_and_decimal(make_model, make_vocabulary):
    model = make_model(text_bonus={"-": 20.0, "3": 15.0, ".": 10.0, "1": 5.0, "4": 5.0})
    vocabulary = make_vocabulary(model)
    text, _ = JSONNumberStep().run(model, vocabulary, [])
    value = json.loads(text)
    assert isinstance(value, (int, float))


def test_json_number_step_terminates_on_zero(make_model, make_vocabulary):
    model = make_model(text_bonus={"0": 100.0})
    vocabulary = make_vocabulary(model)
    text, _ = JSONNumberStep().run(model, vocabulary, [])
    # "0" is complete; the grammar forbids "00" (leading-zero rule), so it must stop at "0".
    assert text == "0"


def test_json_number_step_never_gets_stuck_with_no_preference(make_model, make_vocabulary):
    # Regression test: with a flat/default preference (no text_bonus at all), the
    # decoder used to be able to wander into "-." and then loop appending zeros
    # forever, because the prefix grammar wrongly allowed an omitted integer part
    # once a '.' had been produced. It must always converge on a real number.
    model = make_model()
    vocabulary = make_vocabulary(model)
    text, _ = JSONNumberStep().run(model, vocabulary, [])
    value = json.loads(text)
    assert isinstance(value, (int, float))
