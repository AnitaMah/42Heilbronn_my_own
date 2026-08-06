class Plant:
    def __init__(self, name: str, height: int, age: int) -> None:
        self._name = name
        self._height = height if height >= 0 else 0
        self._age = age if age >= 0 else 0

    def get_name(self) -> str:
        return self._name

    def get_height(self) -> int:
        return self._height

    def set_height(self, new_height: int) -> None:
        if new_height < 0:
            print(
                f"{self._name.capitalize()}: Error, height can't be negative\n"
                "Height update rejected\n"
            )
        else:
            self._height = new_height
            print(f"Height updated: {self._height}cm")

    def get_age(self) -> int:
        return self._age

    def set_age(self, new_age: int) -> None:
        if new_age < 0:
            print(
                f"{self._name.capitalize()}: Error, age can't be negative\n"
                "Age update rejected\n"
            )
        else:
            self._age = new_age
            print(f"Age updated: {self._age} days")


if __name__ == "__main__":
    plant = Plant("Rose", 12, 6)

    print(
        f"Plant created: {plant.get_name().capitalize()}: "
        f"{plant.get_height()}cm, {plant.get_age()} days old"
    )

    plant.set_height(-5)
    plant.set_height(19)
    plant.set_age(-5)
    plant.set_age(9)

    print(
        f"Current state: {plant.get_name().capitalize()}: "
        f"{plant.get_height()}cm, {plant.get_age()} days old"
    )
