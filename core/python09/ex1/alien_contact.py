"""
Cosmic Data Observatory - Alien Contact Log Validation.

Exercise 1: custom validation using @model_validator for
complex business rules that go beyond simple field constraints.
"""

from datetime import datetime
from enum import Enum
from typing import Optional

from pydantic import BaseModel, Field, ValidationError, model_validator


class ContactType(str, Enum):
    """Category of alien contact event."""

    RADIO = "radio"
    VISUAL = "visual"
    PHYSICAL = "physical"
    TELEPATHIC = "telepathic"


class AlienContact(BaseModel):
    """Validated report of an alien contact event."""

    contact_id: str = Field(..., min_length=5, max_length=15)
    timestamp: datetime
    location: str = Field(..., min_length=3, max_length=100)
    contact_type: ContactType
    signal_strength: float = Field(..., ge=0.0, le=10.0)
    duration_minutes: int = Field(..., ge=1, le=1440)
    witness_count: int = Field(..., ge=1, le=100)
    message_received: Optional[str] = Field(default=None, max_length=500)
    is_verified: bool = False

    @model_validator(mode="after")
    def check_business_rules(self) -> "AlienContact":
        """Enforce cross-field rules beyond simple type/range checks.

        mode="after" (not "before") on purpose: by the time this runs,
        every field has already passed its own Field() validation, so
        self.contact_type is guaranteed to already be a real ContactType
        and self.witness_count a real int - these rules can trust that
        and focus purely on the business logic between fields.
        """
        # Rule 1: every contact ID must be tagged as an Alien Contact report
        if not self.contact_id.startswith("AC"):
            raise ValueError('Contact ID must start with "AC"')

        # Rule 2: physical contact is the highest-stakes claim, so it
        # cannot go into the log unverified
        if self.contact_type == ContactType.PHYSICAL and not self.is_verified:
            raise ValueError("Physical contact reports must be verified")

        # Rule 3: telepathic contact is unfalsifiable by nature, so we
        # require corroboration from multiple witnesses
        is_telepathic = self.contact_type == ContactType.TELEPATHIC
        if is_telepathic and self.witness_count < 3:
            raise ValueError(
                "Telepathic contact requires at least 3 witnesses"
            )

        # Rule 4 (the one judgment call in this file): the subject says
        # strong signals "should" include a message, while the other
        # three rules say "must" - I'm still treating it as a hard
        # requirement (raise, not a warning), and reading the boundary
        # as strictly greater-than, so a signal of exactly 7.0 does NOT
        # require a message.
        if self.signal_strength > 7.0 and not self.message_received:
            raise ValueError(
                "Strong signals (>7.0) should include received messages"
            )

        return self


def _print_contact(contact: AlienContact) -> None:
    """Print a contact report's fields in a readable block."""
    print("Valid contact report:")
    print(f"ID: {contact.contact_id}")
    print(f"Type: {contact.contact_type.value}")
    print(f"Location: {contact.location}")
    print(f"Signal: {contact.signal_strength}/10")
    print(f"Duration: {contact.duration_minutes} minutes")
    print(f"Witnesses: {contact.witness_count}")
    if contact.message_received:
        print(f"Message: '{contact.message_received}'")


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


def main() -> None:
    """Demonstrate valid and invalid AlienContact creation.

    Prints one report that passes every rule, then deliberately builds
    a telepathic report with only 1 witness (violates rule 3) so the
    caught ValidationError demonstrates the custom validator, not just
    a plain Field() bound.
    """
    print("Alien Contact Log Validation")
    print("=" * 40)

    valid_contact = AlienContact(
        contact_id="AC_2024_001",
        timestamp=datetime.fromisoformat("2024-03-10T22:15:00"),
        location="Area 51, Nevada",
        contact_type=ContactType.RADIO,
        signal_strength=8.5,
        duration_minutes=45,
        witness_count=5,
        message_received="Greetings from Zeta Reticuli",
    )
    _print_contact(valid_contact)

    print()
    print("=" * 40)
    print("Expected validation error:")
    try:
        AlienContact(
            contact_id="AC_2024_002",
            timestamp=datetime.fromisoformat("2024-03-11T03:00:00"),
            location="Roswell, New Mexico",
            contact_type=ContactType.TELEPATHIC,
            signal_strength=4.0,
            duration_minutes=10,
            witness_count=1,
        )
    except ValidationError as error:
        print(_clean_error_message(error))


if __name__ == "__main__":
    main()
