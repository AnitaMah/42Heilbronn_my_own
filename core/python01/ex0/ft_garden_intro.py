# NOTE: Exercise 0 is meant to introduce basic program structure only.
# The subject explicitly asks for "simple variables" (name, height, age)
# and print(), NOT a class. Classes are only introduced from Exercise 1
# onward. Using a Plant class here goes beyond what this exercise asks for.
class Plant:
    # Constructor: runs automatically when a Plant object is created,
    # stores the three attributes on the instance (self).
    def __init__(self, name: str, height: int, age: int) -> None:

        self.name = name
        self.height = height
        self.age = age

    # Displays the plant's information, one attribute per line.
    def show(self) -> None:

        print(f"Plant: {self.name}")
        # Missing "cm" unit here vs the example output ("Height: 25cm")
        print(f"Height: {self.height}")
        # Missing "days" unit here vs the example output ("Age: 30 days")
        print(f"Age: {self.age}")


# Entry point: this block only runs when the file is executed directly
# (python3 ft_garden_intro.py), not when imported as a module.
if __name__ == "__main__":

    print("=== Welcome to My Garden ===")

    plant = Plant("Rose", 25, 30)
    plant.show()
    # Missing the closing "=== End of Program ===" line from the example.
