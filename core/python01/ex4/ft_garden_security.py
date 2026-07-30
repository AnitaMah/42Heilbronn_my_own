# Garden Security System: this class is meant to protect its data from
# invalid values (negative height/age) via validated setters.
# NOTE: the subject asks to store attributes using the "protected"
# convention (self._height, self._age) so they aren't used directly
# from outside the class. Here they are still public (self.height,
# self.age), and the constructor itself does not validate its inputs
# (e.g. Plant("Rose", -5, -3) would silently succeed) — only
# set_height()/set_age() validate. get_height()/get_age() accessor
# methods, also required by the subject, are not implemented either.
class Plant:
    def __init__(self, name: str, height: int, age: int) -> None:
        self.name = name
        self.height = height
        self.age = age

    # Validated setter: rejects negative heights instead of applying
    # them, printing an error and leaving the existing value unchanged.
    def set_height(self, new_height: int) -> None:
        if new_height < 0:
            print(
                f"{self.name.capitalize()}: Error, height can't be negative\n"
                "Height update rejected\n"
            )
        else:
            self.height = new_height
            print(f"Height updated: {self.height}cm")

    # Validated setter: rejects negative ages the same way set_height()
    # rejects negative heights.
    def set_age(self, new_age: int) -> None:
        if new_age < 0:
            print(
                f"{self.name.capitalize()}: Error, age can't be negative\n"
                "Age update rejected\n"
            )
        else:
            self.age = new_age
            print(f"Age updated: {self.age} days")


if __name__ == "__main__":
    plant = Plant("Rose", 12, 6)

    print(
        f"Plant created: {plant.name.capitalize()}: "
        f"{plant.height}cm, {plant.age} days old"
    )

    plant.set_height(-5)
    plant.set_height(19)
    plant.set_age(-5)
    plant.set_age(9)

    print(
        f"Current state: {plant.name.capitalize()}: "
        f"{plant.height}cm, {plant.age} days old"
    )
