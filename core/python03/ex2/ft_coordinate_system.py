"""!
@file ft_coordinate_system.py
@brief Track 3D player coordinates and compute distances between them.
"""
import math
from typing import Tuple


def get_player_pos() -> Tuple[float, float, float]:
    """!
    @brief Prompt the user for 'x,y,z' coordinates until valid.
    @return A tuple with the parsed (x, y, z) coordinates.
    """
    while True:
        user_input = input(
            "Enter new coordinates as floats in format 'x,y,z': ")

        parts = user_input.split(',')

        if len(parts) != 3:
            print("Invalid syntax")
            continue

        try:
            x, y, z = (float(p) for p in parts)
            return (x, y, z)

        except ValueError:
            for p in parts:
                try:
                    float(p.strip())
                except ValueError:
                    clean_p = p.strip()
                    print(
                        f"Error on parameter '{clean_p}': "
                        f"could not convert string to float: '{clean_p}'"
                    )
                    break


def calculate_distance(
    p1: Tuple[float, float, float],
    p2: Tuple[float, float, float] = (0.0, 0.0, 0.0)
) -> float:
    """!
    @brief Compute the Euclidean distance between two 3D points.
    @param p1 The first (x, y, z) point.
    @param p2 The second (x, y, z) point, defaults to the origin.
    @return The distance between p1 and p2.
    """
    return math.sqrt(
        (p2[0] - p1[0])**2 +
        (p2[1] - p1[1])**2 +
        (p2[2] - p1[2])**2
    )


def main() -> None:
    """!
    @brief Get two coordinate sets and report distances to/between them.
    @return None.
    """
    print("=== Game Coordinate System ===\n")

    print("Get a first set of coordinates")

    pos1 = get_player_pos()
    print(f"Got a first tuple: {pos1}")
    print(f"It includes: X={pos1[0]}, Y={pos1[1]}, Z={pos1[2]}")

    dist_to_center = calculate_distance(pos1)
    print(f"Distance to center: {dist_to_center:.4f}\n")

    print("Get a second set of coordinates")

    pos2 = get_player_pos()
    dist_between = calculate_distance(pos1, pos2)
    print(
        f"Distance between the 2 sets of coordinates: "
        f"{round(dist_between, 4)}"
    )


if __name__ == "__main__":
    main()
