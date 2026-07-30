# NOTE on this file overall: this Plant base class does not carry over
# the previous exercises' work. It has no grow()/age_plant() methods
# (from Ex2/3) and no set_/get_ validation or protected attributes
# (from Ex4) — Ex5 says to "start with your Plant class from the
# previous exercise", so this regresses functionality rather than
# extending it. Attribute names were also shortened to nm/h, which
# breaks the name/height/age convention used everywhere else in the
# project and isn't required or suggested by the subject.
class Plant:
    def __init__(self, nm: str, h: int, age: int) -> None:
        self.nm = nm
        self.h = h
        self.age = age

    # Helper that formats the common "name (height, age)" part of the
    # output. NOTE: the subject expects Plant to have its own show()
    # method that child classes override and extend via super().show()
    # (as Ex6 later does) — using a plain helper method instead of
    # show() means the required super() reuse pattern for show() isn't
    # actually demonstrated here.
    def get_info(self) -> str:
        return f"{self.nm.capitalize()} ({self.h}cm, {self.age} days)"


# Flower: adds a color attribute and blooming behavior on top of Plant.
class Flower(Plant):
    def __init__(self, nm: str, h: int, age: int, color: str) -> None:
        # Reuses Plant's constructor to set up the shared attributes.
        super().__init__(nm, h, age)
        self.color = color

    def show(self) -> None:
        print(f"{self.get_info()}\nColor: {self.color}\n")

    # Blooms once the flower is older than 15 days (arbitrary threshold).
    def blooming(self) -> None:
        status = "is blooming beautifully!" if self.age > 15 else \
                 "has not bloomed yet"
        print(f"{self.nm.capitalize()} {status}\n")


# Tree: adds a trunk diameter and the ability to produce shade.
class Tree(Plant):
    def __init__(self, nm: str, h: int, age: int, t: int, w: int) -> None:
        super().__init__(nm, h, age)
        self.trunk_size = t
        self.w = w

    def show(self) -> None:
        print(f"{self.get_info()}\nTrunk: {self.trunk_size}cm\n")

    def produce_shade(self) -> None:
        print(f"{self.nm.capitalize()} provides {self.w}cm shade.\n")


# Vegetable: adds harvest season + nutritional value.
class Vegetable(Plant):
    def __init__(self, nm: str, h: int, age: int, sea: str, ntr: int) -> None:
        super().__init__(nm, h, age)
        self.sea = sea
        self.ntr = ntr

    def show(self) -> None:
        print(f"{self.get_info()}\nSeason: {self.sea}\n"
              f"Nutrition: {self.ntr}\n")

    # NOTE: the subject wants nutritional_value to increase when BOTH
    # age() and grow() are called separately. Here a single grow()
    # bumps height, age AND nutrition all at once, and there is no
    # separate age() override for Vegetable, so calling age() alone
    # (if it existed) would not raise nutrition as the subject expects.
    def grow(self) -> None:
        self.h += 50
        self.age += 20
        self.ntr += 20


if __name__ == "__main__":
    print("--- GARDEN PLANTS ---\n")

    rose = Flower("Rose", 25, 24, "red")
    rose.show()
    rose.blooming()

    oak = Tree("Oak", 23, 200, 20, 12)
    oak.show()
    oak.produce_shade()

    tomato = Vegetable("Tomato", 20, 10, "July", 0)
    tomato.show()
    tomato.grow()
    print("--- After growth ---")
    tomato.show()
