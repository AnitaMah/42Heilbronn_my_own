import sys

def create_inventory(args):
    inventory = {}

    for arg in args:
        if ":" not in arg:
            print(f"Error -  invalid parameter '{arg}'")
            continue

        item, quantity_str = arg.split(":", 1)

        if item in inventory:
            print(f"Redundant item '{item}' - discarding")
            continue

        try:
            inventory[item] = int(quantity_str)

        except ValueError:
            print(f"Quantity error for '{item}': invalid literal for int() with base 10: '{quantity_str}'")


        return inventory

def print_inventory(inventory):
    print(f"Got inventory: {inventory}")



def analyze_inventory(inventory):
    if not inventory:
        return

    total = sum(inventory.values())

    print(f"Item list: {list(inventory.keys())}")
    print(f"Total quantity of the {len(inventory)} items: {total}")

    for item, qty in inventory.items():
        print(f"Item {item} represents {(qty / total) * 100:.1f}%")

    most = max(inventory, key=inventory.get)
    least = min(inventory, key=inventory.get)
    print(f"Item most abundant: {most} with quantity {inventory[most]}")
    print(f"Item least abundant: {least} with quantity {inventory[least]}")


def main():
    inventory = create_inventory(sys.argv[1:])
    print_inventory(inventory)
    analyze_inventory(inventory)

    inventory['magic_item'] = 1
    print(f"Updated inventory: {inventory}")

if __name__ == "__main__":
    main()
