import random

from src.function_caller import call_function_for_prompt
from src.models import FunctionDefinition
from conftest import scripted_number_targets, scripted_string_target

FUNCTIONS = [
    FunctionDefinition.model_validate(
        {
            "name": "fn_add_numbers",
            "description": "Add two numbers together and return their sum.",
            "parameters": {"a": {"type": "number"}, "b": {"type": "number"}},
            "returns": {"type": "number"},
        }
    ),
    FunctionDefinition.model_validate(
        {
            "name": "fn_greet",
            "description": "Generate a greeting message for a person by name.",
            "parameters": {"name": {"type": "string"}},
            "returns": {"type": "string"},
        }
    ),
    FunctionDefinition.model_validate(
        {
            "name": "fn_reverse_string",
            "description": "Reverse a string and return the reversed result.",
            "parameters": {"s": {"type": "string"}},
            "returns": {"type": "string"},
        }
    ),
]


def test_end_to_end_picks_greet_and_fills_name(make_model, make_vocabulary):
    model = make_model(text_bonus={"g": 30.0, "reverse": -30.0, "add": -30.0})
    model.dynamic_bonus = scripted_string_target(model, "shrek")
    vocabulary = make_vocabulary(model)

    result = call_function_for_prompt(model, vocabulary, "Greet shrek", FUNCTIONS)

    assert result.prompt == "Greet shrek"
    assert result.name == "fn_greet"
    assert result.parameters == {"name": "shrek"}


def test_end_to_end_picks_add_numbers_with_two_arguments(make_model, make_vocabulary):
    model = make_model(text_bonus={"add": 30.0, "greet": -30.0, "reverse": -30.0})
    model.dynamic_bonus = scripted_number_targets(model, {'"a": ': "2", '"b": ': "3"})
    vocabulary = make_vocabulary(model)

    result = call_function_for_prompt(model, vocabulary, "What is the sum of 2 and 3?", FUNCTIONS)

    assert result.name == "fn_add_numbers"
    assert result.parameters["a"] == 2
    assert result.parameters["b"] == 3


def test_output_is_always_schema_valid_regardless_of_model_preference(
    make_model, make_vocabulary, all_pieces
):
    # Fuzz: even with arbitrary (adversarial-ish) logit preferences, the
    # generated call must always name a real function and supply every
    # required argument with the right JSON type.
    rng = random.Random(1234)
    for trial in range(8):
        bonus = {piece: rng.uniform(-5, 5) for piece in all_pieces}
        model = make_model(text_bonus=bonus)
        # Growing preference for the closing quote guarantees every JSON string
        # value eventually terminates, however the (randomized) per-character
        # preferences shake out -- without this a flat random preference for
        # some non-quote character would repeat it forever.
        model.dynamic_bonus = lambda input_ids: {'"': 0.2 * len(input_ids)}
        vocabulary = make_vocabulary(model)

        result = call_function_for_prompt(model, vocabulary, f"random prompt {trial}", FUNCTIONS)

        by_name = {fn.name: fn for fn in FUNCTIONS}
        assert result.name in by_name
        expected_params = by_name[result.name].parameters
        assert set(result.parameters.keys()) == set(expected_params.keys())
        for key, spec in expected_params.items():
            value = result.parameters[key]
            if spec.type == "number":
                assert isinstance(value, (int, float))
            elif spec.type == "string":
                assert isinstance(value, str)
            elif spec.type == "boolean":
                assert isinstance(value, bool)
