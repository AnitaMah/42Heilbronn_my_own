class Plant:
    def __init__(self, name: str, height: float, age: int) -> None:
        self.name = name
        self.height = height
        self.age = age

    def grow(self) -> None:
        if self.name == "Rose":
            self.height += 0.6
        else:
            self.height += 0.4

    def age_plant(self) -> None:
        self.age += 5


if __name__ == "__main__":
    plant = Plant("Camelia", 50.0, 30)

    start_height = plant.height

    for day in range(1, 8):
        print(f"=== Day {day} ===")

        plant.grow()
        plant.age_plant()
        print(
            f"{plant.name}: {round(plant.height, 1)}cm, "
            f"{plant.age} days old"
        )

    growth = plant.height - start_height

    print(f"Growth this week: {round(growth, 1)}cm")
