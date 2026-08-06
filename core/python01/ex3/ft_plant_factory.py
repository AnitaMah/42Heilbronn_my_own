class Plant:
    def __init__(self, name: str, height: int, age: int) -> None:
        self.name = name
        self.height = height
        self.age = age

    def grow(self, height: int) -> None:
        self.height += height

    def age_plant(self, days: int) -> None:
        self.age += days

    def show(self) -> None:
        print(
            f"Created: {self.name}: {self.height}cm, "
            f"{self.age} days old"
        )


if __name__ == "__main__":
    plant = Plant("Rose", 12, 6)

    plant.grow(3)
    plant.age_plant(2)
    plant.show()
