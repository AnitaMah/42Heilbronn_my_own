"""Lambda Sanctum: anonymous functions doing all the heavy lifting.

Sage Lambda does not write named helpers for one-shot transformations
here -- every sort key, filter test, and mapping in this file is a
lambda expression, exactly as the Sanctum demands.
"""


def artifact_sorter(artifacts: list[dict]) -> list[dict]:
    """Sort magical artifacts by 'power' level, strongest first."""
    return sorted(artifacts, key=lambda artifact: artifact["power"],
                  reverse=True)


def power_filter(mages: list[dict], min_power: int) -> list[dict]:
    """Keep only the mages whose 'power' is at least min_power."""
    return list(filter(lambda mage: mage["power"] >= min_power, mages))


def spell_transformer(spells: list[str]) -> list[str]:
    """Wrap every spell name as '* name *'."""
    return list(map(lambda spell: f"* {spell} *", spells))


def mage_stats(mages: list[dict]) -> dict:
    """Summarize a mage roster's power levels.

    Returns {'max_power': int, 'min_power': int, 'avg_power': float}.
    """
    powers = list(map(lambda mage: mage["power"], mages))
    strongest = max(mages, key=lambda mage: mage["power"])
    weakest = min(mages, key=lambda mage: mage["power"])
    return {
        "max_power": strongest["power"],
        "min_power": weakest["power"],
        "avg_power": round(sum(powers) / len(powers), 2),
    }


def main() -> None:
    artifacts = [
        {"name": "Crystal Orb", "power": 85, "type": "relic"},
        {"name": "Fire Staff", "power": 92, "type": "weapon"},
        {"name": "Shadow Cloak", "power": 47, "type": "armor"},
        {"name": "Frost Blade", "power": 78, "type": "weapon"},
    ]
    mages = [
        {"name": "Alex", "power": 55, "element": "fire"},
        {"name": "Jordan", "power": 82, "element": "shadow"},
        {"name": "Riley", "power": 30, "element": "frost"},
        {"name": "Sage Lambda", "power": 99, "element": "arcane"},
    ]
    spells = ["fireball", "heal", "shield"]

    print("Testing artifact sorter...")
    sorted_artifacts = artifact_sorter(artifacts)
    first, second = sorted_artifacts[0], sorted_artifacts[1]
    print(f"{first['name']} ({first['power']} power) comes before "
          f"{second['name']} ({second['power']} power)")

    print("\nTesting power filter...")
    strong_mages = power_filter(mages, 50)
    names = ", ".join(mage["name"] for mage in strong_mages)
    print(f"Mages with power >= 50: {names}")

    print("\nTesting spell transformer...")
    print(" ".join(spell_transformer(spells)))

    print("\nTesting mage stats...")
    stats = mage_stats(mages)
    print(f"Max power: {stats['max_power']}")
    print(f"Min power: {stats['min_power']}")
    print(f"Average power: {stats['avg_power']}")


if __name__ == "__main__":
    main()
