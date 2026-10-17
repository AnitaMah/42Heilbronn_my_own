"""Root-level test script for ex1 (the capabilities exercise).

Run with: python3 capacitor.py
"""

from ex0 import CreatureFactory
from ex1 import HealCapability, HealingCreatureFactory, TransformCapability
from ex1 import TransformCreatureFactory


def test_healing_family(factory: CreatureFactory) -> None:
    """Describe, attack, then heal for both the base and evolved form.

    ``factory.create_base()`` is typed to return a plain ``Creature``,
    so mypy can't know a ``heal()`` method exists on it. An
    ``isinstance`` check narrows the type safely -- no casts, no
    ``# type: ignore`` needed -- and it's exactly the same check
    ex2's ``BattleStrategy.is_valid`` will use later. A factory that
    builds Creatures without the capability gets an error message
    instead of a crash.
    """
    print("Testing Creature with healing capability")

    for label, creature in (
        (" base:", factory.create_base()),
        (" evolved:", factory.create_evolved()),
    ):
        if not isinstance(creature, HealCapability):
            print(f"Error: '{creature.name}' has no healing capability")
            return
        print(label)
        print(creature.describe())
        print(creature.attack())
        print(creature.heal())
    print()


def test_transform_family(factory: CreatureFactory) -> None:
    """Describe, attack, transform, attack again, then revert."""
    print("Testing Creature with transform capability")

    for label, creature in (
        (" base:", factory.create_base()),
        (" evolved:", factory.create_evolved()),
    ):
        if not isinstance(creature, TransformCapability):
            print(f"Error: '{creature.name}' has no transform capability")
            return
        print(label)
        print(creature.describe())
        print(creature.attack())
        print(creature.transform())
        print(creature.attack())
        print(creature.revert())


def main() -> None:
    test_healing_family(HealingCreatureFactory())
    test_transform_family(TransformCreatureFactory())


if __name__ == "__main__":
    main()
