class PlantError(Exception):
    """Raised if we have a PlantError."""
    pass

def water_plant(plant_name):
    """Waters the plant if the name is capitalized, otherwise raises PlantError."""
    if plant_name != plant_name.capitalize():
        raise PlantError(f"Plant name '{plant_name}' is not capitalized!")

    print(f"Watering {plant_name}: [OK]")

def test_watering_system():
    print("=== Garden Watering System ===")

    print("\n")

    print("Testing valid plants...")
    print("Opening watering system")
    try:
        valid_plants = ["Rose", "Lemon", "Carrots"]
        for plant in valid_plants:
            water_plant(plant)
    finally:
        print("Closing watering system")
    print("\n")

    print("Testing invalid plants...")
    print("Opening watering system")
    try:
        invalid_plants = ["Rose", "potato"]
        for plant in invalid_plants:
            water_plant(plant)
    except PlantError as e:
        print(f"Caught {type(e).__name__}: {e}")
        print(".. ending tests and returning to main")
    finally:
        print("Closing watering system")

    print("\n")

    print("Cleanup always happens, even with errors!")

if __name__ == "__main__":
    test_watering_system()
