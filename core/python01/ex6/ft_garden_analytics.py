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
        self.name = name
        self.age = age
        self.height = height
        self.stats = self.Stats()

    def show(self) -> None:
        self.stats.show_calls += 1
        print(f"{self.name}: {self.height}cm, {self.age} days old")

    def grow(self, add_height: float) -> None:
        self.stats.grow_calls += 1
        self.height += add_height
        print(f"{self.name} is growing.")

    def age_plant(self, add_age: int) -> None:
        self.stats.age_calls += 1
        self.age += add_age
        print(f"{self.name}: {self.height}cm, {self.age} days old")

    @staticmethod
    def is_older_than_a_year(days: int) -> bool:
        return days > 365

    @classmethod
    def create_anonymous(cls) -> "Plant":
        return cls("Unknown plant", 0, 0.0)


class Flower(Plant):
    def __init__(self, name: str, age: int, height: float, color: str) -> None:
        super().__init__(name, age, height)
        self.color = color
        self.bloomed = False

    def show(self) -> None:
        super().show()
        print(f"Color: {self.color}")
        if self.bloomed:
            print(f"{self.name} is blooming beautifully!")
        else:
            print(f"{self.name} has not bloomed yet")


class Seed(Flower):
    def __init__(self, name: str, age: int, height: float, color: str) -> None:
        super().__init__(name, age, height, color)
        self.seeds = 0

    def grow(self, add_height: float) -> None:
        super().grow(add_height)
        if self.height > 100:
            self.bloomed = True
            self.seeds = 42

    def show(self) -> None:
        super().show()
        print(f"Seeds: {self.seeds}")


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
        self.d = d
        self.stats: "Tree.TreeStats" = self.TreeStats()

    def show(self) -> None:
        super().show()
        print(f"Trunk diameter: {self.d}cm")

    def produce_shade(self) -> None:
        self.stats.shade_calls += 1
        print(f"Tree {self.name} now produces a shade of {self.height}cm "
              f"long and {self.d}cm wide.")


def display_any_plant_stats(plant: Plant) -> None:
    print(f"[statistics for {plant.name}]")
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
