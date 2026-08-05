"""Root-level test script for ex2 (the strategy exercise).

Run with: python3 tournament.py
"""

from ex0 import CreatureFactory, FlameFactory, AquaFactory
from ex1 import HealingCreatureFactory, TransformCreatureFactory
from ex2 import (
    AggressiveStrategy,
    BattleStrategy,
    DefensiveStrategy,
    InvalidStrategyError,
    NormalStrategy,
)

Opponent = tuple[CreatureFactory, BattleStrategy]


def battle(opponents: list[Opponent]) -> None:
    """Make every opponent fight every other opponent exactly once.

    Each opponent is built once (so state like "am I transformed"
    carries only within its own fights, not across others) and then
    every unique pair fights, acting through its own strategy. If a
    strategy is invalid for the Creature it was paired with, the
    whole tournament stops there -- it does not skip ahead to the
    next pairing.
    """
    print("*** Tournament ***")
    print(f"{len(opponents)} opponents involved")
    print()

    creatures = [
        (factory.create_base(), strategy) for factory, strategy in opponents
    ]

    for i in range(len(creatures)):
        for j in range(i + 1, len(creatures)):
            creature_a, strategy_a = creatures[i]
            creature_b, strategy_b = creatures[j]

            print("* Battle *")
            print(creature_a.describe())
            print(" vs.")
            print(creature_b.describe())
            print(" now fight!")

            try:
                strategy_a.act(creature_a)
                strategy_b.act(creature_b)
            except InvalidStrategyError as exc:
                print(f"Battle error, aborting tournament: {exc}")
                return
            print()


def run_tournament(label: str, description: str, opponents: list[Opponent]) -> None:
    """Print a labeled header, then run one tournament."""
    print(label)
    print(f" {description}")
    battle(opponents)
    print()


def main() -> None:
    run_tournament(
        "Tournament 0 (basic)",
        "[ (Flameling+Normal), (Healing+Defensive) ]",
        [
            (FlameFactory(), NormalStrategy()),
            (HealingCreatureFactory(), DefensiveStrategy()),
        ],
    )

    run_tournament(
        "Tournament 1 (error)",
        "[ (Flameling+Aggressive), (Healing+Defensive) ]",
        [
            (FlameFactory(), AggressiveStrategy()),
            (HealingCreatureFactory(), DefensiveStrategy()),
        ],
    )

    run_tournament(
        "Tournament 2 (multiple)",
        "[ (Aquabub+Normal), (Healing+Defensive), (Transform+Aggressive) ]",
        [
            (AquaFactory(), NormalStrategy()),
            (HealingCreatureFactory(), DefensiveStrategy()),
            (TransformCreatureFactory(), AggressiveStrategy()),
        ],
    )


if __name__ == "__main__":
    main()
