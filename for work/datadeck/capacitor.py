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
    ex2's ``BattleStrategy.is_valid`` will use later.
    """
    print("Testing Creature with healing capability")

    base = factory.create_base()
    assert isinstance(base, HealCapability)
    print(" base:")
    print(base.describe())
    print(base.attack())
    print(base.heal())

    evolved = factory.create_evolved()
    assert isinstance(evolved, HealCapability)
    print(" evolved:")
    print(evolved.describe())
    print(evolved.attack())
    print(evolved.heal())
    print()


def test_transform_family(factory: CreatureFactory) -> None:
    """Describe, attack, transform, attack again, then revert."""
    print("Testing Creature with transform capability")

    for label, creature in (
        (" base:", factory.create_base()),
        (" evolved:", factory.create_evolved()),
    ):
        assert isinstance(creature, TransformCapability)
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
