"""
Cosmic Data Observatory - Space Station Data Validation.

Exercise 0: basic Pydantic model creation with BaseModel and Field.
"""

from datetime import datetime
from typing import Optional

from pydantic import BaseModel, Field, ValidationError


class SpaceStation(BaseModel):
    """Validated data for a single space station report.

    Every field below is checked purely with Field() constraints - no
    custom validator is needed yet, since none of these rules depend on
    another field's value (that comes in ex1/ex2). Numeric bounds use
    ge/le (inclusive) because the subject's ranges are closed intervals,
    e.g. "1-20 people" includes both 1 and 20.
    """

    station_id: str = Field(..., min_length=3, max_length=10)
    name: str = Field(..., min_length=1, max_length=50)
    crew_size: int = Field(..., ge=1, le=20)
    power_level: float = Field(..., ge=0.0, le=100.0)
    oxygen_level: float = Field(..., ge=0.0, le=100.0)
    # No Field() constraint here on purpose: Pydantic auto-converts an
    # ISO-8601 string into a real datetime, which is the behavior the
    # subject's "Think About" box is pointing at.
    last_maintenance: datetime
    is_operational: bool = True
    # The only field where absence is itself valid - hence Optional
    # with a default instead of a required Field(...).
    notes: Optional[str] = Field(default=None, max_length=200)


def _print_station(station: SpaceStation) -> None:
    """Print a station's fields in a readable block."""
    print("Valid station created:")
    print(f"ID: {station.station_id}")
    print(f"Name: {station.name}")
    print(f"Crew: {station.crew_size} people")
    print(f"Power: {station.power_level}%")
    print(f"Oxygen: {station.oxygen_level}%")
    status = "Operational" if station.is_operational else "Offline"
    print(f"Status: {status}")


def main() -> None:
    """Demonstrate valid and invalid SpaceStation creation.

    Builds one valid station and prints it, then deliberately builds
    an invalid one (crew_size over the limit) inside try/except so the
    ValidationError is caught and reported instead of crashing the
    program - this is what "protect the data stream from corruption"
    means in practice for this exercise.
    """
    print("Space Station Data Validation")
    print("=" * 40)

    valid_station = SpaceStation(
        station_id="ISS001",
        name="International Space Station",
        crew_size=6,
        power_level=85.0,
        oxygen_level=92.3,
        last_maintenance=datetime.fromisoformat("2024-01-15T08:00:00"),
    )
    _print_station(valid_station)

    print()
    print("=" * 40)
    print("Expected validation error:")
    try:
        SpaceStation(
            station_id="ISS002",
            name="Overcrowded Station",
            crew_size=25,
            power_level=80.0,
            oxygen_level=90.0,
            last_maintenance=datetime.fromisoformat("2024-01-15T08:00:00"),
        )
    except ValidationError as error:
        first_error = error.errors()[0]
        print(first_error["msg"])


if __name__ == "__main__":
    main()
