"""Strategy pattern: how a Creature acts during a tournament.

Without this, ``tournament.py`` would need to know, for every single
Creature it fights, whether it should heal or transform -- an
if/elif chain that grows with every new family. Instead each Creature
is paired with a strategy object, and the tournament just calls
``act()`` without caring what's inside.
"""

from abc import ABC, abstractmethod

from ex0.creature import Creature
from ex1.capability import HealCapability, TransformCapability


class InvalidStrategyError(Exception):
    """Raised when ``act()`` is called on a Creature the strategy can't handle."""


class BattleStrategy(ABC):
    """Abstract strategy: can this Creature use me, and if so, how?"""

    @abstractmethod
    def is_valid(self, creature: Creature) -> bool:
        """Return True if this strategy can be applied to ``creature``."""
        raise NotImplementedError

    @abstractmethod
    def act(self, creature: Creature) -> None:
        """Perform this strategy's actions for ``creature``, printing each step.

        Must raise ``InvalidStrategyError`` if ``is_valid(creature)``
        would have returned False -- callers are expected to check
        first, but ``act`` never trusts that blindly.
        """
        raise NotImplementedError


class NormalStrategy(BattleStrategy):
    """Suitable for any Creature: just attack."""

    def is_valid(self, creature: Creature) -> bool:
        return True

    def act(self, creature: Creature) -> None:
        print(creature.attack())


class AggressiveStrategy(BattleStrategy):
    """Suitable for Creatures with TransformCapability: transform, attack, revert."""

    def is_valid(self, creature: Creature) -> bool:
        return isinstance(creature, TransformCapability)

    def act(self, creature: Creature) -> None:
        if not self.is_valid(creature):
            raise InvalidStrategyError(
                f"Invalid Creature '{creature.name}' for this aggressive strategy"
            )
        assert isinstance(creature, TransformCapability)
        print(creature.transform())
        print(creature.attack())
        print(creature.revert())


class DefensiveStrategy(BattleStrategy):
    """Suitable for Creatures with HealCapability: attack, then heal."""

    def is_valid(self, creature: Creature) -> bool:
        return isinstance(creature, HealCapability)

    def act(self, creature: Creature) -> None:
        if not self.is_valid(creature):
            raise InvalidStrategyError(
                f"Invalid Creature '{creature.name}' for this defensive strategy"
            )
        assert isinstance(creature, HealCapability)
        print(creature.attack())
        print(creature.heal())
