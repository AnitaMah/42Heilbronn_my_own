"""
Cosmic Data Observatory - Space Crew Management Validation.

Exercise 2: nested Pydantic models and validation rules that
reason across a list of related sub-models.
"""

from datetime import datetime
from enum import Enum
from typing import List

from pydantic import BaseModel, Field, ValidationError, model_validator


class Rank(str, Enum):
    """Crew member rank, from lowest to highest seniority."""

    CADET = "cadet"
    OFFICER = "officer"
    LIEUTENANT = "lieutenant"
    CAPTAIN = "captain"
    COMMANDER = "commander"


class CrewMember(BaseModel):
    """A single crew member assigned to a mission."""

    member_id: str = Field(..., min_length=3, max_length=10)
    name: str = Field(..., min_length=2, max_length=50)
    rank: Rank
    age: int = Field(..., ge=18, le=80)
    specialization: str = Field(..., min_length=3, max_length=30)
    years_experience: int = Field(..., ge=0, le=50)
    is_active: bool = True


class SpaceMission(BaseModel):
    """A mission with its full crew roster and safety requirements."""

    mission_id: str = Field(..., min_length=5, max_length=15)
    mission_name: str = Field(..., min_length=3, max_length=100)
    destination: str = Field(..., min_length=3, max_length=50)
    launch_date: datetime
    duration_days: int = Field(..., ge=1, le=3650)
    crew: List[CrewMember] = Field(..., min_length=1, max_length=12)
    mission_status: str = "planned"
    budget_millions: float = Field(..., ge=1.0, le=10000.0)

    @model_validator(mode="after")
    def check_safety_requirements(self) -> "SpaceMission":
        """Enforce mission-level rules that depend on the crew list."""
        # Rule 1: mission IDs are tagged with the launch program prefix
        if not self.mission_id.startswith("M"):
            raise ValueError('Mission ID must start with "M"')

        # Rule 2: every mission needs a senior officer in command
        has_command_rank = any(
            member.rank in (Rank.COMMANDER, Rank.CAPTAIN)
            for member in self.crew
        )
        if not has_command_rank:
            raise ValueError(
                "Mission must have at least one Commander or Captain"
            )

        # Rule 3: long missions are riskier, so at least half the crew
        # must be seasoned (5+ years experience)
        if self.duration_days > 365:
            experienced = sum(
                1 for member in self.crew if member.years_experience >= 5
            )
            if experienced / len(self.crew) < 0.5:
                raise ValueError(
                    "Long missions (>365 days) need 50% experienced crew "
                    "(5+ years)"
                )

        # Rule 4: nobody inactive should be on an active mission roster
        if not all(member.is_active for member in self.crew):
            raise ValueError("All crew members must be active")

        return self


def _clean_error_message(error: ValidationError) -> str:
    """Return the first error's message without Pydantic's prefix.

    A ValueError raised inside a model_validator is wrapped by Pydantic
    as "Value error, <message>" - this strips that prefix so custom
    business-rule errors read the same as built-in Field errors.
    """
    message = error.errors()[0]["msg"]
    prefix = "Value error, "
    if message.startswith(prefix):
        return message[len(prefix):]
    return message


def _print_mission(mission: SpaceMission) -> None:
    """Print a mission and its crew roster in a readable block."""
    print("Valid mission created:")
    print(f"Mission: {mission.mission_name}")
    print(f"ID: {mission.mission_id}")
    print(f"Destination: {mission.destination}")
    print(f"Duration: {mission.duration_days} days")
    print(f"Budget: ${mission.budget_millions}M")
    print(f"Crew size: {len(mission.crew)}")
    print("Crew members:")
    for member in mission.crew:
        print(
            f"- {member.name} ({member.rank.value}) - "
            f"{member.specialization}"
        )


def main() -> None:
    """Demonstrate valid and invalid SpaceMission creation."""
    print("Space Mission Crew Validation")
    print("=" * 40)

    valid_mission = SpaceMission(
        mission_id="M2024_MARS",
        mission_name="Mars Colony Establishment",
        destination="Mars",
        launch_date=datetime.fromisoformat("2024-06-01T09:00:00"),
        duration_days=900,
        budget_millions=2500.0,
        crew=[
            CrewMember(
                member_id="CM001",
                name="Sarah Connor",
                rank=Rank.COMMANDER,
                age=42,
                specialization="Mission Command",
                years_experience=15,
            ),
            CrewMember(
                member_id="CM002",
                name="John Smith",
                rank=Rank.LIEUTENANT,
                age=35,
                specialization="Navigation",
                years_experience=8,
            ),
            CrewMember(
                member_id="CM003",
                name="Alice Johnson",
                rank=Rank.OFFICER,
                age=29,
                specialization="Engineering",
                years_experience=6,
            ),
        ],
    )
    _print_mission(valid_mission)

    print()
    print("=" * 40)
    print("Expected validation error:")
    try:
        SpaceMission(
            mission_id="M2024_TEST",
            mission_name="Short Survey Run",
            destination="Lunar Orbit",
            launch_date=datetime.fromisoformat("2024-07-01T09:00:00"),
            duration_days=14,
            budget_millions=50.0,
            crew=[
                CrewMember(
                    member_id="CM010",
                    name="Bob Martian",
                    rank=Rank.OFFICER,
                    age=31,
                    specialization="Piloting",
                    years_experience=4,
                ),
            ],
        )
    except ValidationError as error:
        print(_clean_error_message(error))


if __name__ == "__main__":
    main()
