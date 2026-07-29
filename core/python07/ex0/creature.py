"""Core Creature hierarchy for the DataDeck card system.

This module defines the abstract ``Creature`` card and the concrete
Fire/Water species used by the abstract factories in ``factory.py``.
It is intentionally NOT re-exported from ``ex0/__init__.py``: callers
are only meant to talk to a ``CreatureFactory``, never to a concrete
Creature class directly. That keeps the "which class am I actually
instantiating" decision in one place (the factory).
"""

from abc import ABC, abstractmethod


class Creature(ABC):
    """Abstract base for every card in the game.

    Holds the two pieces of data every Creature shares (a name and a
    type) plus one concrete, inherited-for-free method (``describe``)
    and one abstract method that every subclass must supply
    (``attack``).
    """

    def __init__(self, name: str, type_: str) -> None:
        self.name = name
        self.type_ = type_

    @abstractmethod
    def attack(self) -> str:
        """Return a description of this Creature's attack."""
        raise NotImplementedError

    def describe(self) -> str:
        """Return the standard 'X is a Y type Creature' line.

        This is deliberately concrete (not abstract): every Creature
        describes itself the same way, so there is nothing for
        subclasses to override here.
        """
        return f"{self.name} is a {self.type_} type Creature"


class Flameling(Creature):
    """Base form of the Fire family."""

    def __init__(self, name: str = "Flameling") -> None:
        super().__init__(name, "Fire")

    def attack(self) -> str:
        return f"{self.name} uses Ember!"


class Pyrodon(Creature):
    """Evolved form of the Fire family."""

    def __init__(self, name: str = "Pyrodon") -> None:
        super().__init__(name, "Fire/Flying")

    def attack(self) -> str:
        return f"{self.name} uses Flamethrower!"


class Aquabub(Creature):
    """Base form of the Water family."""

    def __init__(self, name: str = "Aquabub") -> None:
        super().__init__(name, "Water")

    def attack(self) -> str:
        return f"{self.name} uses Water Gun!"


class Torragon(Creature):
    """Evolved form of the Water family."""

    def __init__(self, name: str = "Torragon") -> None:
        super().__init__(name, "Water")

    def attack(self) -> str:
        return f"{self.name} uses Hydro Pump!"
