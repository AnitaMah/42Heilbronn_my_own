class Plant:
    class Stats:
        def __init__(self) -> None:
            self.grow_calls = 0
            self.age_calls = 0
            self.show_calls = 0

        def display(self) -> None:
            print(f"Stats: {self.grow_calls} grow, {self.age_calls} age, "
                  f"{self.show_calls} show")

    def __init__(self, name: str, age: int = 0, height: float = 0.0) -> None:
        self._name = name
        self._age = age if age >= 0 else 0
        self._height = height if height >= 0 else 0.0
        self.stats = self.Stats()

    def get_name(self) -> str:
        return self._name

    def get_height(self) -> float:
        return self._height

    def set_height(self, new_height: float) -> None:
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

    def show(self) -> None:
        self.stats.show_calls += 1
        print(f"{self._name}: {self._height}cm, {self._age} days old")

    def grow(self, add_height: float) -> None:
        self.stats.grow_calls += 1
        self._height += add_height
        print(f"{self._name} is growing.")

    def age_plant(self, add_age: int) -> None:
        self.stats.age_calls += 1
        self._age += add_age
        print(f"{self._name}: {self._height}cm, {self._age} days old")

    @staticmethod
    def is_older_than_a_year(days: int) -> bool:
        return days > 365

    @classmethod
    def create_anonymous(cls) -> "Plant":
        return cls("Unknown plant", 0, 0.0)


class Flower(Plant):
    def __init__(self, name: str, age: int, height: float, color: str) -> None:
        super().__init__(name, age, height)
        self._color = color
        self._bloomed = False

    def get_color(self) -> str:
        return self._color

    def set_color(self, new_color: str) -> None:
        self._color = new_color
        print(f"Color updated: {self._color}")

    def is_bloomed(self) -> bool:
        return self._bloomed

    def set_bloomed(self, new_bloomed: bool) -> None:
        self._bloomed = new_bloomed
        print(f"Bloomed status updated: {self._bloomed}")

    def show(self) -> None:
        super().show()
        print(f"Color: {self._color}")
        if self._bloomed:
            print(f"{self.get_name()} is blooming beautifully!")
        else:
            print(f"{self.get_name()} has not bloomed yet")


class Seed(Flower):
    def __init__(self, name: str, age: int, height: float, color: str) -> None:
        super().__init__(name, age, height, color)
        self._seeds = 0

    def get_seeds(self) -> int:
        return self._seeds

    def set_seeds(self, new_seeds: int) -> None:
        if new_seeds < 0:
            print(
                f"{self.get_name().capitalize()}: Error, seeds can't be "
                "negative\nSeeds update rejected\n"
            )
        else:
            self._seeds = new_seeds
            print(f"Seeds updated: {self._seeds}")

    def grow(self, add_height: float) -> None:
        super().grow(add_height)
        if self.get_height() > 100:
            self._bloomed = True
            self._seeds = 42

    def show(self) -> None:
        super().show()
        print(f"Seeds: {self._seeds}")


class Tree(Plant):
    class TreeStats(Plant.Stats):
        def __init__(self) -> None:
            super().__init__()
            self.shade_calls = 0

        def display(self) -> None:
            super().display()
            print(f"{self.shade_calls} shade")

    def __init__(self, name: str, age: int, height: float, d: float) -> None:
        super().__init__(name, age, height)
        self._d = d if d >= 0 else 0.0
        self.stats: "Tree.TreeStats" = self.TreeStats()

    def get_diameter(self) -> float:
        return self._d

    def set_diameter(self, new_diameter: float) -> None:
        if new_diameter < 0:
            print(
                f"{self.get_name().capitalize()}: Error, diameter can't "
                "be negative\nDiameter update rejected\n"
            )
        else:
            self._d = new_diameter
            print(f"Trunk diameter updated: {self._d}cm")

    def show(self) -> None:
        super().show()
        print(f"Trunk diameter: {self._d}cm")

    def produce_shade(self) -> None:
        self.stats.shade_calls += 1
        print(f"Tree {self.get_name()} now produces a shade of "
              f"{self.get_height()}cm long and {self._d}cm wide.")


def display_any_plant_stats(plant: Plant) -> None:
    print(f"[statistics for {plant.get_name()}]")
    plant.stats.display()


if __name__ == "__main__":
    print("=== Garden statistics ===")
    print("=== Check year-old")
    print(f"Is 30 days more than a year? -> {Plant.is_older_than_a_year(30)}")
    print(
        f"Is 400 days more than a year? -> "
        f"{Plant.is_older_than_a_year(400)}"
    )

    print("\n=== Flower")
    rose = Flower("Rose", 10, 15.5, "red")
    rose.show()
    display_any_plant_stats(rose)

    print("\n=== Tree")
    oak = Tree("Oak", 365, 200.0, 5.0)
    oak.show()
    display_any_plant_stats(oak)
    print("[asking the oak to produce shade]")
    oak.produce_shade()
    display_any_plant_stats(oak)

    print("\n=== Seed")
    sun = Seed("Sunflower", 45, 80.0, "yellow")
    sun.show()
    print("[make sunflower grow, age and bloom]")
    sun.grow(30)
    sun.age_plant(10)
    sun.show()
    display_any_plant_stats(sun)

    print("\n=== Anonymous")
    anon = Plant.create_anonymous()
    anon.show()
    display_any_plant_stats(anon)
