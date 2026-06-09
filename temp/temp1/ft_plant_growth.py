class Plant:
    def __init__(self, name, height, age):
        self.name = name
        self.height = height
        self.age = age

    def grow(self):
        if self.name == "Rose":
            self.height += 0.8
        else:
            self.height += 0.5
    def age_plant(self):
        self.age += 5
if __name__ == "__main__":
    plant = Plant("Camelia", 50.0, 30)
    start_height = plant.height
    for day in range(1, 8):
        print(f"=== Day {day} ===")
        plant.grow()
        plant,age_plant()
        print(f"{plant.name}: {round(plant.height, 1)}cm, {plant.age} days old")
    growth = plant.height - start_height
    print(f"Growth this week: {round(growth, 1)}cm")
