"""Root-level test script for ex0 (the abstract factory exercise).

Run with: python3 battle.py
"""

from ex0 import AquaFactory, CreatureFactory, FlameFactory


def test_factory(factory: CreatureFactory) -> None:
    """Prove a factory can build, describe, and attack with both forms.

    Takes any ``CreatureFactory`` -- it never needs to know if it
    received a FlameFactory or an AquaFactory. That's the payoff of
    the pattern: this function works for every family, present and
    future, with zero changes.
    """
    print("Testing factory")
    base = factory.create_base()
    print(base.describe())
    print(base.attack())

    evolved = factory.create_evolved()
    print(evolved.describe())
    print(evolved.attack())
    print()


def test_battle(factory_a: CreatureFactory, factory_b: CreatureFactory) -> None:
    """Make each factory's base Creature fight the other's."""
    print("Testing battle")
    creature_a = factory_a.create_base()
    creature_b = factory_b.create_base()

    print(creature_a.describe())
    print(" vs.")
    print(creature_b.describe())
    print(" fight!")
    print(creature_a.attack())
    print(creature_b.attack())


def main() -> None:
    flame_factory = FlameFactory()
    aqua_factory = AquaFactory()

    test_factory(flame_factory)
    test_factory(aqua_factory)
    test_battle(flame_factory, aqua_factory)


if __name__ == "__main__":
    main()
