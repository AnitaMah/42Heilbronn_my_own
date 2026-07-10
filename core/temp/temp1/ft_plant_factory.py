class Plant:
    def __init__(self, name, start_height, starting_age):
        self.name = name
        self.start_height = start_height
        self.starting_age = starting_age

    def grow(self, height:int) -> None:
        self.start_height += 50
    def age(self, days:int) ->None:
        self.starting_age += days

    def show(self):
        print(f"Created: {self.name}: {self.start_height}cm, {self.starting_age} days old")


if __name__ == "__main__":
    plant1 = Plant("Rose", 12, 6)
    plant1.grow(3)
    plant1.age(5)
    plant1.show()
