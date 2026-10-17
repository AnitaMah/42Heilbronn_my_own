"""Capability mixins.

These abstract classes deliberately do NOT inherit from ``Creature``.
A capability describes something a card can *do*, not what it *is*.
That separation is what lets ``Sproutling`` be "a Creature that can
heal" instead of "a HealingCreature", and lets the same capability be
reused later on a card type that has nothing to do with Creature at
all.
"""

from abc import ABC, abstractmethod
from typing import Optional


class HealCapability(ABC):
    """Grants a ``heal`` action. Stateless: just describes the effect."""

    @abstractmethod
    def heal(self, target: Optional[object] = None) -> str:
        """Return a description of the healing performed.

        ``target`` is optional and untyped on purpose: a capability
        module has no business knowing about ``Creature`` at all, so
        it can't (and shouldn't) type ``target`` as one.
        """
        raise NotImplementedError


class TransformCapability(ABC):
    """Grants ``transform``/``revert``, backed by persistent state.

    Unlike ``HealCapability``, this one is stateful: whether the card
    is currently transformed changes how it behaves elsewhere (in
    practice, it changes what ``attack()`` returns on the Creature
    that mixes this in).
    """

    def __init__(self) -> None:
        self._transformed: bool = False

    @property
    def is_transformed(self) -> bool:
        return self._transformed

    @abstractmethod
    def transform(self) -> str:
        """Switch into the transformed state and describe it."""
        raise NotImplementedError

    @abstractmethod
    def revert(self) -> str:
        """Switch back to the normal state and describe it."""
        raise NotImplementedError
