# Reuses the Plant model from Exercise 1 and adds behavior: plants can
# now change their own state over time via grow() and age_plant().
class Plant:
    def __init__(self, name: str, height: float, age: int) -> None:
        self.name = name
        self.height = height
        self.age = age

    # Grows the plant by a fixed amount per call. Different plants grow
    # at different rates (here based on name) to show that grow() can
    # behave differently depending on the plant.
    # NOTE: method is named "age_plant" instead of "age" (see below) to
    # avoid clashing with the self.age attribute; the subject's grow()
    # is kept as-is since it doesn't collide with an attribute name.
    def grow(self) -> None:
        if self.name == "Rose":
            self.height += 0.6
        else:
            self.height += 0.4

    # Ages the plant. Named age_plant() rather than age() because a
    # method can't share its name with the self.age attribute.
    def age_plant(self) -> None:
        self.age += 5


if __name__ == "__main__":
    plant = Plant("Camelia", 50.0, 30)

    # Remember the starting height so we can compute the week's
    # total growth at the end.
    start_height = plant.height

    # Simulate 7 days: each iteration grows and ages the plant once,
    # then prints its current state.
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
