"""Ancient Library: treasures from functools and operator.

Archivist Functools keeps four artifacts on display: reduce for
folding a sequence into one value, partial for pre-loading a spell's
arguments, lru_cache for memoizing expensive recursion, and
singledispatch for picking behaviour by argument type.
"""

import operator
from functools import lru_cache, partial, reduce, singledispatch
from collections.abc import Callable
from typing import Any


def spell_reducer(spells: list[int], operation: str) -> int:
    """Fold spells into a single value using functools.reduce.

    Supported operations: 'add', 'multiply', 'max', 'min'.
    """
    if not spells:
        return 0
    operations: dict[str, Callable[[int, int], int]] = {
        "add": operator.add,
        "multiply": operator.mul,
        "max": max,
        "min": min,
    }
    if operation not in operations:
        raise ValueError(f"Unknown operation: {operation!r}")
    return reduce(operations[operation], spells)


def partial_enchanter(base_enchantment: Callable) -> dict[str, Callable]:
    """Pre-fill base_enchantment(power, element, target) three ways.

    Each returned spell already has power=50 and its element baked in;
    only target is left to supply.
    """
    return {
        "fire": partial(base_enchantment, 50, "Fire"),
        "water": partial(base_enchantment, 50, "Water"),
        "lightning": partial(base_enchantment, 50, "Lightning"),
    }


@lru_cache(maxsize=None)
def memoized_fibonacci(n: int) -> int:
    """Return the nth Fibonacci number, memoized with lru_cache."""
    if n < 2:
        return n
    return memoized_fibonacci(n - 1) + memoized_fibonacci(n - 2)


def spell_dispatcher() -> Callable[[Any], str]:
    """Build a functools.singledispatch spell system and return it."""

    @singledispatch
    def cast(spell: Any) -> str:
        return f"Unknown spell type: {type(spell).__name__}"

    @cast.register
    def _(spell: int) -> str:
        return f"Damage spell: {spell} damage"

    @cast.register
    def _(spell: str) -> str:
        return f"Enchantment: {spell}"

    @cast.register
    def _(spell: list) -> str:
        return f"Multi-cast: {len(spell)} spells"

    return cast


def _enchant(power: int, element: str, target: str) -> str:
    """Sample base enchantment used to demonstrate partial_enchanter."""
    return f"{element} enchantment ({power} power) applied to {target}"


def main() -> None:
    print("Testing spell reducer...")
    powers = [10, 20, 30, 40]
    print(f"Sum: {spell_reducer(powers, 'add')}")
    print(f"Product: {spell_reducer(powers, 'multiply')}")
    print(f"Max: {spell_reducer(powers, 'max')}")

    print("\nTesting partial enchanter...")
    enchantments = partial_enchanter(_enchant)
    print(enchantments["fire"]("Sword"))
    print(enchantments["water"]("Shield"))

    print("\nTesting memoized fibonacci...")
    print(f"Fib(0): {memoized_fibonacci(0)}")
    print(f"Fib(1): {memoized_fibonacci(1)}")
    print(f"Fib(10): {memoized_fibonacci(10)}")
    print(f"Fib(15): {memoized_fibonacci(15)}")
    print(f"Cache info: {memoized_fibonacci.cache_info()}")

    print("\nTesting spell dispatcher...")
    cast = spell_dispatcher()
    print(cast(42))
    print(cast("fireball"))
    print(cast([1, 2, 3]))
    print(cast(3.14))


if __name__ == "__main__":
    main()
