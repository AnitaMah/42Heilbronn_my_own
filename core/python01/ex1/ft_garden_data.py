class Plant:
    def __init__(self, name: str, height: float, age: int) -> None:

        self.name = name
        self.height = height
        self.age = age

    def show(self) -> None:
        print(f"{self.name}: {self.height}cm, {self.age} days old")


if __name__ == "__main__":

    print("=== Garden Plant Registry ===")

    plant1 = Plant("Peony", 30, 20)
    plant2 = Plant("Lilac", 120, 45)
    plant3 = Plant("Hydrangea", 80, 140)

    plant1.show()
    plant2.show()
    plant3.show()
