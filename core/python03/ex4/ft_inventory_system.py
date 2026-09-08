"""!
@file ft_inventory_system.py
@brief Build and analyze an inventory from command-line parameters.
"""
import sys
from typing import Dict, List


def create_inventory(args: List[str]) -> Dict[str, int]:
    """!
    @brief Parse '<item>:<quantity>' arguments into an inventory dict.
    @param args Raw command-line parameters to parse.
    @return A dictionary mapping item names to integer quantities.
    """
    inventory: Dict[str, int] = {}

    for arg in args:
        if ":" not in arg:
            print(f"Error - invalid parameter '{arg}'")
            continue

        item, quantity_str = arg.split(":", 1)

        if item in inventory:
            print(f"Redundant item '{item}' - discarding")
            continue

        try:
            inventory[item] = int(quantity_str)
        except ValueError:
            print(f"Quantity error for '{item}': invalid literal "
                  f"for int() with base 10: '{quantity_str}'")

    return inventory


def print_inventory(inventory: Dict[str, int]) -> None:
    """!
    @brief Print the raw inventory dictionary.
    @param inventory The inventory to display.
    @return None.
    """
    print(f"Got inventory: {inventory}")


def analyze_inventory(inventory: Dict[str, int]) -> None:
    """!
    @brief Report totals, percentages and the min/max items in stock.
    @param inventory The inventory to analyze.
    @return None.
    """
    if not inventory:
        return

    total = sum(inventory.values())

    print(f"Item list: {list(inventory.keys())}")
    print(f"Total quantity of the {len(inventory)} items: {total}")

    for item, qty in inventory.items():
        print(f"Item {item} represents {(qty / total) * 100:.1f}%")

    most = max(inventory, key=lambda k: inventory[k])
    least = min(inventory, key=lambda k: inventory[k])
    print(f"Item most abundant: {most} with quantity {inventory[most]}")
    print(f"Item least abundant: {least} with quantity {inventory[least]}")


def main() -> None:
    """!
    @brief Build the inventory from argv, analyze it, then add an item.
    @return None.
    """
    inventory = create_inventory(sys.argv[1:])
    print_inventory(inventory)
    analyze_inventory(inventory)

    inventory['magic_item'] = 1
    print(f"Updated inventory: {inventory}")


if __name__ == "__main__":
    main()
