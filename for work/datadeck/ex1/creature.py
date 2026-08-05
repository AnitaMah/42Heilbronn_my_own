"""Two new Creature families built by mixing in a capability.

Each class here inherits from BOTH ``Creature`` (for name/type/attack)
and one capability class (for the extra action). Neither capability
knows these classes exist -- the coupling only goes one way.
"""

from ex0.creature import Creature
from ex1.capability import HealCapability, TransformCapability


class Sproutling(Creature, HealCapability):
    """Base form of the Grass/Healing family."""

    def __init__(self, name: str = "Sproutling") -> None:
        Creature.__init__(self, name, "Grass")

    def attack(self) -> str:
        return f"{self.name} uses Vine Whip!"

    def heal(self, target: object = None) -> str:
        return f"{self.name} heals itself for a small amount"


class Bloomelle(Creature, HealCapability):
    """Evolved form of the Grass/Healing family."""

    def __init__(self, name: str = "Bloomelle") -> None:
        Creature.__init__(self, name, "Grass/Fairy")

    def attack(self) -> str:
        return f"{self.name} uses Petal Dance!"

    def heal(self, target: object = None) -> str:
        return f"{self.name} heals itself and others for a large amount"


class Shiftling(Creature, TransformCapability):
    """Base form of the Normal/Transform family."""

    def __init__(self, name: str = "Shiftling") -> None:
        Creature.__init__(self, name, "Normal")
        TransformCapability.__init__(self)

    def attack(self) -> str:
        if self.is_transformed:
            return f"{self.name} performs a boosted strike!"
        return f"{self.name} attacks normally."

    def transform(self) -> str:
        self._transformed = True
        return f"{self.name} shifts into a sharper form!"

    def revert(self) -> str:
        self._transformed = False
        return f"{self.name} returns to normal."


class Morphagon(Creature, TransformCapability):
    """Evolved form of the Normal/Transform family."""

    def __init__(self, name: str = "Morphagon") -> None:
        Creature.__init__(self, name, "Normal/Dragon")
        TransformCapability.__init__(self)

    def attack(self) -> str:
        if self.is_transformed:
            return f"{self.name} unleashes a devastating morph strike!"
        return f"{self.name} attacks normally."

    def transform(self) -> str:
        self._transformed = True
        return f"{self.name} morphs into a dragonic battle form!"

    def revert(self) -> str:
        self._transformed = False
        return f"{self.name} stabilizes its form."
