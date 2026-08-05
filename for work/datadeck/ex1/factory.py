"""Factories for the two capability-driven families.

Same abstract factory pattern as ex0 -- inherits ``CreatureFactory``
so ex2's tournament code can treat every family (ex0 or ex1) exactly
the same way.
"""

from ex0.creature import Creature
from ex0.factory import CreatureFactory
from ex1.creature import Bloomelle, Morphagon, Shiftling, Sproutling


class HealingCreatureFactory(CreatureFactory):
    """Builds the Healing family: Sproutling -> Bloomelle."""

    def create_base(self) -> Creature:
        return Sproutling()

    def create_evolved(self) -> Creature:
        return Bloomelle()


class TransformCreatureFactory(CreatureFactory):
    """Builds the Transform family: Shiftling -> Morphagon."""

    def create_base(self) -> Creature:
        return Shiftling()

    def create_evolved(self) -> Creature:
        return Morphagon()
