def light_spell_allowed_ingredients():
    return ["earth", "air", "fire", "water"]

def light_spell_record(spell_name, ingredients):
    from .light_validator import validate_ingredients  # Lazy import
    validation = validate_ingredients(ingredients)
    return f"Spell recorded: {spell_name} ({validation})"