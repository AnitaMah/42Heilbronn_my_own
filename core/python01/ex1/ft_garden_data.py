# Plant is now a reusable model/blueprint: instead of tracking each
# plant's data in separate loose variables, every plant becomes an
# instance of this class, sharing the same attributes and behavior.
class Plant:
    # Sets each new instance's name/height/age when it is created.
    def __init__(self, name: str, height: float, age: int) -> None:

        self.name = name
        self.height = height
        self.age = age

    # Prints this single plant's info in the required registry format.
    def show(self) -> None:
        print(f"{self.name}: {self.height}cm, {self.age} days old")


if __name__ == "__main__":

    print("=== Garden Plant Registry ===")

    # Three separate Plant instances, each with its own data
    # (satisfies the "at least 3 plants" requirement).
    plant1 = Plant("Peony", 30, 20)
    plant2 = Plant("Lilac", 120, 45)
    plant3 = Plant("Hydrangea", 80, 140)

    plant1.show()
    plant2.show()
    plant3.show()
