"""Generate realistic space-themed test data for the python09 exercises.

Produces plain dicts (not Pydantic models) so they can be fed into
whichever SpaceStation / AlienContact / SpaceMission models you write
for ex0, ex1 and ex2. Each generator can produce a "valid" record that
satisfies the subject's business rules, or a deliberately "invalid" one
to exercise your validators.
"""

from __future__ import annotations

import random
from datetime import datetime, timedelta
from typing import Any

STATION_NAMES = [
    "International Space Station", "Artemis Outpost", "Europa Relay",
    "Ganymede Research Base", "Titan Observatory", "Mars Orbital Hub",
    "Lunar Gateway", "Kepler Watch", "Proxima Relay", "Andromeda Beacon",
]

CONTACT_LOCATIONS = [
    "Area 51, Nevada", "Roswell, New Mexico", "Rendlesham Forest, UK",
    "Nazca Plateau, Peru", "Tunguska, Siberia", "Bermuda Triangle",
    "Antarctic Ice Shelf", "Sahara Desert", "Pine Gap, Australia",
    "Mount Shasta, California",
]

CONTACT_TYPES = ["radio", "visual", "physical", "telepathic"]

CONTACT_MESSAGES = [
    "Greetings from Zeta Reticuli",
    "We come in peace",
    "Coordinates transmission incomplete",
    "Signal repeats every 37 seconds",
]

FIRST_NAMES = ["Sarah", "John", "Alice", "Marcus", "Elena", "Yuki", "Omar", "Priya"]
LAST_NAMES = ["Connor", "Smith", "Johnson", "Vega", "Petrov", "Tanaka", "Haddad", "Rao"]

RANKS = ["cadet", "officer", "lieutenant", "captain", "commander"]
SENIOR_RANKS = ["captain", "commander"]

SPECIALIZATIONS = [
    "Navigation", "Engineering", "Mission Command", "Medical",
    "Xenobiology", "Communications", "Pilot", "Life Support",
]

DESTINATIONS = ["Mars", "Europa", "Titan", "Alpha Centauri", "The Moon", "Ceres"]

MISSION_NAMES = [
    "Mars Colony Establishment", "Europa Ice Drill", "Titan Survey",
    "Deep Space Relay", "Lunar Mining Expedition", "Ceres Outpost Build",
]


def _random_datetime(days_back: int = 365) -> datetime:
    """Random datetime within `days_back` days of now (negative = future)."""
    offset_days = random.randint(0, abs(days_back))
    if days_back < 0:
        offset_days = -offset_days
    return datetime.now() - timedelta(
        days=offset_days,
        hours=random.randint(0, 23),
        minutes=random.randint(0, 59),
    )


def generate_space_station(index: int, valid: bool = True) -> dict[str, Any]:
    """Return one SpaceStation record (ex0)."""
    station = {
        "station_id": f"ST{index:03d}",
        "name": random.choice(STATION_NAMES),
        "crew_size": random.randint(1, 20),
        "power_level": round(random.uniform(0.0, 100.0), 1),
        "oxygen_level": round(random.uniform(0.0, 100.0), 1),
        "last_maintenance": _random_datetime().isoformat(),
        "is_operational": random.choice([True, True, True, False]),
        "notes": random.choice([None, "Routine check completed", "Awaiting resupply"]),
    }
    if not valid:
        station["crew_size"] = random.choice([0, 25])
    return station


def generate_alien_contact(index: int, valid: bool = True) -> dict[str, Any]:
    """Return one AlienContact record (ex1)."""
    contact_type = random.choice(CONTACT_TYPES)
    witness_count = random.randint(3, 15) if contact_type == "telepathic" else random.randint(1, 15)
    signal_strength = round(random.uniform(0.0, 10.0), 1)
    message = random.choice(CONTACT_MESSAGES) if signal_strength > 7.0 else None

    contact = {
        "contact_id": f"AC_{2024}_{index:03d}",
        "timestamp": _random_datetime(days_back=30).isoformat(),
        "location": random.choice(CONTACT_LOCATIONS),
        "contact_type": contact_type,
        "signal_strength": signal_strength,
        "duration_minutes": random.randint(1, 1440),
        "witness_count": witness_count,
        "message_received": message,
        "is_verified": True if contact_type == "physical" else random.choice([True, False]),
    }
    if not valid:
        broken_rule = random.choice(["bad_prefix", "unverified_physical", "few_witnesses"])
        if broken_rule == "bad_prefix":
            contact["contact_id"] = f"XX_{2024}_{index:03d}"
        elif broken_rule == "unverified_physical":
            contact["contact_type"] = "physical"
            contact["is_verified"] = False
        else:
            contact["contact_type"] = "telepathic"
            contact["witness_count"] = 1
    return contact


def generate_crew_member(index: int, force_senior: bool = False) -> dict[str, Any]:
    """Return one CrewMember record, nested inside a SpaceMission (ex2)."""
    rank = random.choice(SENIOR_RANKS) if force_senior else random.choice(RANKS)
    return {
        "member_id": f"CM{index:03d}",
        "name": f"{random.choice(FIRST_NAMES)} {random.choice(LAST_NAMES)}",
        "rank": rank,
        "age": random.randint(18, 80),
        "specialization": random.choice(SPECIALIZATIONS),
        "years_experience": random.randint(0, 50),
        "is_active": True,
    }


def generate_space_mission(index: int, valid: bool = True) -> dict[str, Any]:
    """Return one SpaceMission record with a nested crew list (ex2)."""
    crew_size = random.randint(2, 8)
    duration_days = random.randint(30, 900)
    crew = [generate_crew_member(i, force_senior=(i == 0)) for i in range(crew_size)]

    if duration_days > 365:
        experienced_needed = (crew_size + 1) // 2
        for member in crew[:experienced_needed]:
            member["years_experience"] = random.randint(5, 50)

    mission = {
        "mission_id": f"M{2024}_{random.choice(DESTINATIONS).upper()[:4]}{index:02d}",
        "mission_name": random.choice(MISSION_NAMES),
        "destination": random.choice(DESTINATIONS),
        "launch_date": _random_datetime(days_back=-180).isoformat(),
        "duration_days": duration_days,
        "crew": crew,
        "mission_status": "planned",
        "budget_millions": round(random.uniform(1.0, 10000.0), 1),
    }
    if not valid:
        broken_rule = random.choice(["no_leader", "inactive_crew"])
        if broken_rule == "no_leader":
            for member in crew:
                if member["rank"] in SENIOR_RANKS:
                    member["rank"] = "officer"
        else:
            crew[0]["is_active"] = False
    return mission


GENERATORS = {
    "space_station": generate_space_station,
    "alien_contact": generate_alien_contact,
    "space_mission": generate_space_mission,
}


def generate_dataset(
    kind: str, count: int, invalid_ratio: float = 0.2
) -> list[dict[str, Any]]:
    """Generate `count` records of the given kind, some deliberately invalid."""
    if kind not in GENERATORS:
        raise ValueError(f"Unknown kind {kind!r}, expected one of {list(GENERATORS)}")
    generator = GENERATORS[kind]
    dataset = []
    for i in range(1, count + 1):
        is_valid = random.random() >= invalid_ratio
        dataset.append(generator(i, valid=is_valid))
    return dataset


def main() -> None:
    for kind in GENERATORS:
        print(f"\n{kind} sample:")
        print(generate_dataset(kind, count=1)[0])


if __name__ == "__main__":
    main()
