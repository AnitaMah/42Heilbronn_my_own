"""Abstract factory pattern: one factory per Creature family.

Each concrete factory knows how to build exactly one family's base
and evolved Creature. Callers never need to know which concrete
Creature class gets constructed -- they just ask the factory for
"the base one" or "the evolved one".
"""

from abc import ABC, abstractmethod

from ex0.creature import Aquabub, Creature, Flameling, Pyrodon, Torragon


class CreatureFactory(ABC):
    """Abstract factory: builds a base and an evolved Creature."""

    @abstractmethod
    def create_base(self) -> Creature:
        """Build the base-form Creature for this family."""
        raise NotImplementedError

    @abstractmethod
    def create_evolved(self) -> Creature:
        """Build the evolved-form Creature for this family."""
        raise NotImplementedError


class FlameFactory(CreatureFactory):
    """Builds the Fire family: Flameling -> Pyrodon."""

    def create_base(self) -> Creature:
        return Flameling()

    def create_evolved(self) -> Creature:
        return Pyrodon()


class AquaFactory(CreatureFactory):
    """Builds the Water family: Aquabub -> Torragon."""

    def create_base(self) -> Creature:
        return Aquabub()

    def create_evolved(self) -> Creature:
        return Torragon()
