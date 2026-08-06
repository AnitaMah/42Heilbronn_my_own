class Plant:
    def __init__(self, nm: str, h: int, age: int) -> None:
        self._nm = nm
        self._h = h if h >= 0 else 0
        self._age = age if age >= 0 else 0

    def get_name(self) -> str:
        return self._nm

    def get_height(self) -> int:
        return self._h

    def set_height(self, new_height: int) -> None:
        if new_height < 0:
            print(
                f"{self._nm.capitalize()}: Error, height can't be negative\n"
                "Height update rejected\n"
            )
        else:
            self._h = new_height
            print(f"Height updated: {self._h}cm")

    def get_age(self) -> int:
        return self._age

    def set_age(self, new_age: int) -> None:
        if new_age < 0:
            print(
                f"{self._nm.capitalize()}: Error, age can't be negative\n"
                "Age update rejected\n"
            )
        else:
            self._age = new_age
            print(f"Age updated: {self._age} days")

    def get_info(self) -> str:
        return f"{self._nm.capitalize()} ({self._h}cm, {self._age} days)"


class Flower(Plant):
    def __init__(self, nm: str, h: int, age: int, color: str) -> None:
        super().__init__(nm, h, age)
        self._color = color

    def get_color(self) -> str:
        return self._color

    def set_color(self, new_color: str) -> None:
        self._color = new_color
        print(f"Color updated: {self._color}")

    def show(self) -> None:
        print(f"{self.get_info()}\nColor: {self._color}\n")

    def blooming(self) -> None:
        status = "is blooming beautifully!" if self.get_age() > 15 else \
                 "has not bloomed yet"
        print(f"{self.get_name().capitalize()} {status}\n")


class Tree(Plant):
    def __init__(self, nm: str, h: int, age: int, t: int, w: int) -> None:
        super().__init__(nm, h, age)
        self._trunk_size = t if t >= 0 else 0
        self._w = w if w >= 0 else 0

    def get_trunk_size(self) -> int:
        return self._trunk_size

    def set_trunk_size(self, new_trunk_size: int) -> None:
        if new_trunk_size < 0:
            print(
                f"{self.get_name().capitalize()}: Error, trunk size can't "
                "be negative\nTrunk size update rejected\n"
            )
        else:
            self._trunk_size = new_trunk_size
            print(f"Trunk size updated: {self._trunk_size}cm")

    def get_shade_width(self) -> int:
        return self._w

    def set_shade_width(self, new_width: int) -> None:
        if new_width < 0:
            print(
                f"{self.get_name().capitalize()}: Error, shade width can't "
                "be negative\nShade width update rejected\n"
            )
        else:
            self._w = new_width
            print(f"Shade width updated: {self._w}cm")

    def show(self) -> None:
        print(f"{self.get_info()}\nTrunk: {self._trunk_size}cm\n")

    def produce_shade(self) -> None:
        print(f"{self.get_name().capitalize()} provides {self._w}cm shade.\n")


class Vegetable(Plant):
    def __init__(self, nm: str, h: int, age: int, sea: str, ntr: int) -> None:
        super().__init__(nm, h, age)
        self._sea = sea
        self._ntr = ntr if ntr >= 0 else 0

    def get_season(self) -> str:
        return self._sea

    def set_season(self, new_season: str) -> None:
        self._sea = new_season
        print(f"Season updated: {self._sea}")

    def get_nutrition(self) -> int:
        return self._ntr

    def set_nutrition(self, new_nutrition: int) -> None:
        if new_nutrition < 0:
            print(
                f"{self.get_name().capitalize()}: Error, nutrition can't "
                "be negative\nNutrition update rejected\n"
            )
        else:
            self._ntr = new_nutrition
            print(f"Nutrition updated: {self._ntr}")

    def show(self) -> None:
        print(f"{self.get_info()}\nSeason: {self._sea}\n"
              f"Nutrition: {self._ntr}\n")

    def grow(self) -> None:
        self._h += 50
        self._age += 20
        self._ntr += 20


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
