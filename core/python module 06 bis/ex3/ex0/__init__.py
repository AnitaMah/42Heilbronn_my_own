"""Public surface of ex0: factories only.

Concrete Creature classes (Flameling, Pyrodon, Aquabub, Torragon)
stay inside ``creature.py`` and are never imported here. Anything
outside this package should only ever hold a ``CreatureFactory``.
"""

from ex0.factory import AquaFactory, CreatureFactory, FlameFactory

__all__ = ["CreatureFactory", "FlameFactory", "AquaFactory"]
