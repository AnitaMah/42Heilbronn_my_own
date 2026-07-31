class PlantError(Exception):
    """Raised if we have a PlantError."""

    def __init__(self, message: str = "Unknown plant error") -> None:
        super().__init__(message)


def water_plant(plant_name: str) -> None:
    """Waters the plant if capitalized, otherwise raises PlantError."""
    if plant_name != plant_name.capitalize():
        raise PlantError(f"Invalid plant name to water: '{plant_name}'")

    print(f"Watering {plant_name}: [OK]")


def test_watering_system() -> None:
    print("=== Garden Watering System ===")

    print("\nTesting valid plants...")
    print("Opening watering system")
    try:
        valid_plants = ["Tomato", "Lettuce", "Carrots"]
        for plant in valid_plants:
            water_plant(plant)
    finally:
        print("Closing watering system")

    print("\nTesting invalid plants...")
    print("Opening watering system")
    try:
        invalid_plants = ["Tomato", "lettuce"]
        for plant in invalid_plants:
            water_plant(plant)
    except PlantError as e:
        print(f"Caught {type(e).__name__}: {e}")
        print(".. ending tests and returning to main")
    finally:
        print("Closing watering system")

    print("\nCleanup always happens, even with errors!")


if __name__ == "__main__":
    test_watering_system()
