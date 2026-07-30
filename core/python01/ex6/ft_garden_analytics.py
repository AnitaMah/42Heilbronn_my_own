# NOTE on this file overall: like Ex5, this Plant base class is
# rebuilt from scratch again rather than extending Ex4's version — the
# protected-attribute / get_/set_ validation work from Ex4 is not
# carried over here either. The constructor's parameter order is also
# swapped (name, age, height) compared to the name/height/age order
# used consistently in Ex0-Ex4.
class Plant:
    # Nested class: each Plant owns a private-ish statistics tracker
    # counting how many times grow()/age_plant()/show() were called.
    # NOTE: subject requires encapsulation here too; grow_calls,
    # age_calls and show_calls are still plain public attributes
    # (no leading underscore), so nothing actually prevents external
    # code from reading/overwriting them directly.
    class Stats:
        def __init__(self) -> None:
            self.grow_calls = 0
            self.age_calls = 0
            self.show_calls = 0

        # Required "display function" for the stats.
        def display(self) -> None:
            print(f"Stats: {self.grow_calls} grow, {self.age_calls} age, "
                  f"{self.show_calls} show")

    def __init__(self, name: str, age: int = 0, height: float = 0.0) -> None:
        self.name = name
        self.age = age
        self.height = height
        # Each plant gets its own independent Stats instance.
        self.stats = self.Stats()

    def show(self) -> None:
        self.stats.show_calls += 1
        print(f"{self.name}: {self.height}cm, {self.age} days old")

    def grow(self, add_height: float) -> None:
        self.stats.grow_calls += 1
        self.height += add_height

    def age_plant(self, add_age: int) -> None:
        self.stats.age_calls += 1
        self.age += add_age

    # Static method: doesn't need an instance, just checks a raw value.
    # Matches the subject's requirement exactly.
    @staticmethod
    def is_older_than_a_year(days: int) -> bool:
        return days > 365

    # Class method: alternate constructor for building a placeholder
    # "anonymous" plant when full information isn't known yet.
    @classmethod
    def create_anonymous(cls) -> "Plant":
        return cls("Unknown plant", 0, 0.0)


# Flower reuses Plant's show() via super().show() and just adds the
# color + bloomed status on top — a clean example of the requested
# "override that re-uses the parent's existing code" pattern.
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


# Seed extends Flower (inheritance chain): once a Seed-flower grows
# past 100cm it blooms and produces 42 seeds.
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
    # TreeStats extends Plant.Stats to add a shade-call counter,
    # reusing display() via super() the same way Flower reuses show().
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
        # Replaces the base Stats with the tree-specific TreeStats.
        self.stats: "Tree.TreeStats" = self.TreeStats()

    def show(self) -> None:
        super().show()
        print(f"Trunk diameter: {self.d}cm")

    def produce_shade(self) -> None:
        self.stats.shade_calls += 1
        print(f"Tree {self.name} now produces a shade of {self.height}cm "
              f"long and {self.d}cm wide.")


# Standalone function (not a method of any class) that can display
# stats for any plant, regardless of its concrete type — satisfies the
# "unique function... for any kind of plant" requirement.
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
