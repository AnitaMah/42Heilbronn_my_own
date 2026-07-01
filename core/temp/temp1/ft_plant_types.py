class Plant:
    def __init__(self, name, height, age):
        self.name = name
        self.height = height
        self.age = age


class Flower(Plant):
    def __init__(self, name: str, height: int, age: int, color: str) -> None:
        super().__init__(name, height, age)
        self.color = color

    def show(self):
        print(f"{self.name.capitalize()} {self.height} cm {self.age} days old\n")
        print(f"Color: {self.color}\n")

    def blooming(self):
        if self.age > 15:
            print(f"{self.name.capitalize()} is blooming beautifully!\n")
        else:
            print(f"{self.name.capitalize()} has not bloomed yet\n")


class Tree(Plant):
    def __init__(self, name, height, age, trunk_size, wide):
        super().__init__(name, height, age)
        self.trunk_size = trunk_size
        self.wide = wide

    def show(self):
        print(f"{self.name.capitalize()} {self.height} cm {self.age} days old\n")
        print(f"Trunk size: {self.trunk_size} cm\n")

    def produce_shade(self):
        print(f"{self.name.capitalize()} produces shade {self.wide} cm wide.")

class Vegetable(Plant):
    def __init__(self, name, height, age, harvest_season, nutritional_value):
        super().__init__(name, height, age)
        self.harvest_season = harvest_season
        self.nutritional_value = nutritional_value
    def show(self):
        print(f"{self.name.capitalize()} {self.height} cm {self.age} days old\n")
        print(f"Harvest season: {self.harvest_season}\n")
        print(f"Nutritional_value: {self.nutritional_value}\n")
    def grow(self):
        self.height += 50
        self.age += 20
        self.nutritional_value += 20


if __name__ == "__main__":
    print("=== Garden Plant Types ===\n")

    print("=== Flower ===")
    rose = Flower("Rose", 25, 24, "red")
    rose.show()
    rose.blooming()

    print("=== Tree ===")
    oak = Tree("Oak", 23, 200, 20, 12)
    oak.show()
    oak.produce_shade()

    print("=== Vegetable ===")
    tomato = Vegetable("Tomato", 20, 10, "July", 0)
    tomato.show()
    tomato.grow()
    tomato.show()
