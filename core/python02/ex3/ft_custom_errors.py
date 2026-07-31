class GardenError(Exception):
    """Base error for all garden-related problems."""

    def __init__(self, message: str = "Unknown garden error") -> None:
        super().__init__(message)


class PlantError(GardenError):
    """Raised when there is a problem with a plant."""

    def __init__(self, message: str = "Unknown plant error") -> None:
        super().__init__(message)


class WaterError(GardenError):
    """Raised when there is a problem with watering."""

    def __init__(self, message: str = "Unknown water error") -> None:
        super().__init__(message)


def check_plant(is_wilting: bool) -> None:
    if is_wilting:
        raise PlantError("The tomato plant is wilting!")


def check_water(liters_in_tank: int) -> None:
    if liters_in_tank <= 0:
        raise WaterError("Not enough water in the tank!")


def _fail_plant() -> None:
    check_plant(is_wilting=True)


def _fail_water() -> None:
    check_water(liters_in_tank=0)


def ft_custom_errors() -> None:
    print("=== Custom Garden Errors Demo ===")

    print("\nTesting PlantError...")
    try:
        check_plant(is_wilting=True)
    except PlantError as e:
        print(f"Caught PlantError: {e}")

    print("\nTesting WaterError...")
    try:
        check_water(liters_in_tank=0)
    except WaterError as e:
        print(f"Caught WaterError: {e}")

    print("\nTesting catching all garden errors...")
    for check in (_fail_plant, _fail_water):
        try:
            check()
        except GardenError as e:
            print(f"Caught GardenError: {e}")

    print("\nAll custom error types work correctly!")


if __name__ == "__main__":
    ft_custom_errors()
