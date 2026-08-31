"""Master's Tower: decorators, staticmethod, and class methods.

Grandmaster Decorator's final test: wrap functions without losing
their identity (functools.wraps), gate them by argument, retry them
on failure, and show how @staticmethod differs from an instance
method that calls back into a decorated helper.
"""

import time
from functools import wraps
from collections.abc import Callable


def spell_timer(func: Callable) -> Callable:
    """Decorator: print how long func took to run, then its result."""
    @wraps(func)
    def wrapper(*args, **kwargs):
        print(f"Casting {func.__name__}...")
        start = time.perf_counter()
        result = func(*args, **kwargs)
        elapsed = time.perf_counter() - start
        print(f"Spell completed in {elapsed:.3f} seconds")
        return result

    return wrapper


def power_validator(min_power: int) -> Callable:
    """Decorator factory: only run the wrapped spell if power is enough.

    Meant for a standalone function whose first argument is power.
    """
    def decorator(func: Callable) -> Callable:
        @wraps(func)
        def wrapper(power: int, *args, **kwargs):
            if power >= min_power:
                return func(power, *args, **kwargs)
            return "Insufficient power for this spell"

        return wrapper

    return decorator


def retry_spell(max_attempts: int) -> Callable:
    """Decorator factory: retry the wrapped spell up to max_attempts."""
    def decorator(func: Callable) -> Callable:
        @wraps(func)
        def wrapper(*args, **kwargs):
            for attempt in range(1, max_attempts + 1):
                try:
                    return func(*args, **kwargs)
                except Exception:
                    if attempt == max_attempts:
                        return (f"Spell casting failed after "
                                f"{max_attempts} attempts")
                    print(f"Spell failed, retrying... "
                          f"(attempt {attempt}/{max_attempts})")
            return None

        return wrapper

    return decorator


class MageGuild:
    """A guild that vets mage names and casts spells on their behalf."""

    @staticmethod
    def validate_mage_name(name: str) -> bool:
        """A mage name is valid if it's letters/spaces, 3+ characters."""
        return len(name) >= 3 and all(
            c.isalpha() or c == " " for c in name
        )

    def cast_spell(self, spell_name: str, power: int) -> str:
        """Cast spell_name at the given power, gated by power_validator."""
        @power_validator(min_power=10)
        def _do_cast(power: int) -> str:
            return f"Successfully cast {spell_name} with {power} power"

        return _do_cast(power)


@spell_timer
def fireball() -> str:
    """Sample spell used to demonstrate spell_timer."""
    time.sleep(0.1)
    return "Fireball cast!"


@retry_spell(max_attempts=3)
def cursed_spell() -> str:
    """Sample spell that always fails, to demonstrate retry_spell."""
    raise RuntimeError("The spell backfires!")


def main() -> None:
    print("Testing spell timer...")
    print(f"Result: {fireball()}")

    print("\nTesting retrying spell...")
    print(cursed_spell())

    print("\nTesting MageGuild...")
    print(MageGuild.validate_mage_name("Riley"))
    print(MageGuild.validate_mage_name("R2"))

    guild = MageGuild()
    print(guild.cast_spell("Lightning", 15))
    print(guild.cast_spell("Lightning", 5))


if __name__ == "__main__":
    main()
