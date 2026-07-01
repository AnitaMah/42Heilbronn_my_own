class GartenError(Exception):
    """Raised when we have Garten errors"""
    pass

class EmptyGartenNameError(GartenError):
    """Raised when the Garten name is an empty string."""
    pass

class NotValidAge(GartenError):
    """Raised when Garten age less than 0"""
    pass
class NoPlantsInGarten(GartenError):
    """Raised when numbers of plans less than 0"""
    pass

class PlantError(GartenError):
    """Raised if we have PlantError"""
    pass

class EmptyPlansName(PlantError):
    """Raised if plant name is empty"""
    pass

class WiltingError(PlantError):
    """Raised if plant is wiltibng"""
    pass

class WatterError(GartenError):
    """Raised if we got WatterError"""
    pass
class NoWaterinTank(WatterError):
    """Raised if we don't have watter in tank"""
    pass

class Garten:
    def __init__(self, name, number_of_plant, age):
        if not name or name.strip() == "":
            raise EmptyGartenNameError("The Garten name cannot be empty!")
        self.name = name
        if number_of_plant < 0:
            raise NoPlantsInGarten("The Garten dosen't has a plants")
        self.number_of_plant = number_of_plant
        if age < 0:
            raise NotValidAge("The age cannot be less than 0")
        self.age = age

class Plant:
    def __init__(self, name, height, age, last_wattering):
        if not name or name.strip() == "":
            raise EmptyPlansName("The name of plant cannot be empty")

        self.name = name
        self.height = height
        self.age = age
        if last_wattering > 5:
            raise WiltingError(f"The {self.name} is wilting")
        self.last_wattering = last_wattering

class Watter:
    def __init__(self, liter_in_tank):

        if liter_in_tank <= 0:
            raise NoWaterinTank("No water in tank")

        self.liter_in_tank = liter_in_tank

def ft_custom_errors():
    print("=== Custom Garden Errors Demo ===")
    print("\n")

    try:
        print("Testing PlantError...")
        Plant(name="", height=10, age=2, last_wattering=6)

    except PlantError as e:
        print(f"Caught PlantError: {e}")

    print("\n")

    try:
        print("Testing WaterError...")
        Watter(liter_in_tank=0)

    except WatterError as e:
        print(f"Caught WaterError: {e}")

    print("\n")

    print("Testing catching all garden errors...")

    test_cases = [
        lambda: Garten(name="Villa", number_of_plant=5, age=-1),
        lambda: Plant(name="Potato", height=4, age=3, last_wattering=6),
        lambda: Watter(liter_in_tank=-1)
    ]

    for test in test_cases:
        try:
            test()
        except GartenError as e:
            print(f"Caught GartenError: {e}")

    print("\n")

    print("All custom error types work correctly!")

if __name__ == "__main__":
    ft_custom_errors()
