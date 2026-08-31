"""Higher Realm: functions that take and return other functions.

Every spell in the grimoire shares the same contract:

    def spell(target: str, power: int) -> str

Mage Functional's tools below combine, amplify, gate, and chain those
spells without ever caring which concrete spell they were handed --
that is what makes them higher-order.
"""

from collections.abc import Callable


def spell_combiner(spell1: Callable, spell2: Callable) -> Callable:
    """Return a spell that casts spell1 and spell2, as a tuple result."""
    def combined(target: str, power: int) -> tuple:
        return (spell1(target, power), spell2(target, power))
    return combined


def power_amplifier(base_spell: Callable, multiplier: int) -> Callable:
    """Return base_spell with its power multiplied before casting."""
    def amplified(target: str, power: int) -> str:
        return base_spell(target, power * multiplier)
    return amplified


def conditional_caster(condition: Callable, spell: Callable) -> Callable:
    """Return a spell that only casts when condition(target, power) holds."""
    def guarded(target: str, power: int) -> str:
        if condition(target, power):
            return spell(target, power)
        return "Spell fizzled"
    return guarded


def spell_sequence(spells: list[Callable]) -> Callable:
    """Return a spell that casts every spell in spells, in order."""
    def sequenced(target: str, power: int) -> list:
        return [spell(target, power) for spell in spells]
    return sequenced


def fireball(target: str, power: int) -> str:
    """Sample spell: a straightforward damage bolt."""
    return f"Fireball hits {target}"


def heal(target: str, power: int) -> str:
    """Sample spell: restore HP."""
    return f"Heals {target}"


def has_mana(target: str, power: int) -> bool:
    """Sample condition: a spell only fires with positive power."""
    return power > 0


def shield(target: str, power: int) -> str:
    """Sample spell: raise a barrier."""
    return f"Shield protects {target} with {power} strength"


def main() -> None:
    print("Testing spell combiner...")
    combined = spell_combiner(fireball, heal)
    result = combined("Dragon", 10)
    print(f"Combined spell result: {result[0]}, {result[1]}")

    print("\nTesting power amplifier...")
    mega_fireball = power_amplifier(shield, 3)
    print("Original: 10, Amplified: 30")
    print(mega_fireball("Dragon", 10))

    print("\nTesting conditional caster...")
    safe_shield = conditional_caster(has_mana, shield)
    print(safe_shield("Party", 15))
    print(safe_shield("Party", 0))

    print("\nTesting spell sequence...")
    combo = spell_sequence([fireball, heal, shield])
    for line in combo("Golem", 20):
        print(line)

    print(f"\ncallable(fireball) -> {callable(fireball)}")
    print(f"callable('not a spell') -> {callable('not a spell')}")


if __name__ == "__main__":
    main()
