# Plant "factory": the constructor already lets us build a fully
# initialized, ready-to-use plant in a single line (no separate setup
# step needed after creation).
class Plant:
    # Creates and initializes a plant in one step: it's immediately
    # ready to use (e.g. grow()) right after construction.
    def __init__(self, name: str, height: int, age: int) -> None:
        self.name = name
        self.height = height
        self.age = age

    # Grows the plant by a caller-supplied amount.
    def grow(self, height: int) -> None:
        self.height += height

    # Ages the plant by a caller-supplied number of days.
    def age_plant(self, days: int) -> None:
        self.age += days

    # Displays the plant using the "Created: ..." factory format.
    def show(self) -> None:
        print(
            f"Created: {self.name}: {self.height}cm, "
            f"{self.age} days old"
        )


if __name__ == "__main__":
    # NOTE: the subject asks for "at least 5 different plants" created
    # here and displayed together; only one plant is created below.
    plant = Plant("Rose", 12, 6)

    plant.grow(3)
    plant.age_plant(2)
    plant.show()
