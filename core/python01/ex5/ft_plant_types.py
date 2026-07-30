class Plant:
    def __init__(self, nm: str, h: int, age: int) -> None:
        self.nm = nm
        self.h = h
        self.age = age

    def get_info(self) -> str:
        return f"{self.nm.capitalize()} ({self.h}cm, {self.age} days)"


class Flower(Plant):
    def __init__(self, nm: str, h: int, age: int, color: str) -> None:
        super().__init__(nm, h, age)
        self.color = color

    def show(self) -> None:
        print(f"{self.get_info()}\nColor: {self.color}\n")

    def blooming(self) -> None:
        status = "is blooming beautifully!" if self.age > 15 else \
                 "has not bloomed yet"
        print(f"{self.nm.capitalize()} {status}\n")


class Tree(Plant):
    def __init__(self, nm: str, h: int, age: int, t: int, w: int) -> None:
        super().__init__(nm, h, age)
        self.trunk_size = t
        self.w = w

    def show(self) -> None:
        print(f"{self.get_info()}\nTrunk: {self.trunk_size}cm\n")

    def produce_shade(self) -> None:
        print(f"{self.nm.capitalize()} provides {self.w}cm shade.\n")


class Vegetable(Plant):
    def __init__(self, nm: str, h: int, age: int, sea: str, ntr: int) -> None:
        super().__init__(nm, h, age)
        self.sea = sea
        self.ntr = ntr

    def show(self) -> None:
        print(f"{self.get_info()}\nSeason: {self.sea}\n"
              f"Nutrition: {self.ntr}\n")

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
