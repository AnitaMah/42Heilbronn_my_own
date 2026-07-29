"""Public surface of ex1: factories and capabilities, no concrete Creatures.

Concrete classes (Sproutling, Bloomelle, Shiftling, Morphagon) stay in
``creature.py``. The capability abstractions are exposed because they
are not Creatures -- ex2 needs them to check which strategies are
valid for a given card.
"""

from ex1.capability import HealCapability, TransformCapability
from ex1.factory import HealingCreatureFactory, TransformCreatureFactory

__all__ = [
    "HealCapability",
    "TransformCapability",
    "HealingCreatureFactory",
    "TransformCreatureFactory",
]
