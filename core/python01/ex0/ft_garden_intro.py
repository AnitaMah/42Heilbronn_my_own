class Plant:
    def __init__(self, name: str, height: int, age: int) -> None:

        self.name = name
        self.height = height
        self.age = age

    def show(self) -> None:

        print(f"Plant: {self.name}")
        print(f"Height: {self.height}")
        print(f"Age: {self.age}")


if __name__ == "__main__":

    print("=== Welcome to My Garden ===")

    plant = Plant("Rose", 25, 30)
    plant.show()
