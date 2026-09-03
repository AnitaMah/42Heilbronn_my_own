from .dark_validator import validate_ingredients  # ❌ Causes ImportError


def dark_spell_allowed_ingredients():
    return ["bats", "frogs", "arsenic", "eyeball"]


def dark_spell_record(spell_name, ingredients):
    validation = validate_ingredients(ingredients)
    return f"Spell recorded: {spell_name} ({validation})"
