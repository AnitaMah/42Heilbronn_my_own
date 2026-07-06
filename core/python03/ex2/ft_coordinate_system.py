import math

def get_player_pos():
    while True:
        user_input = input("Enter new coordinates as floats in format 'x,y,z': ")

        parts = user_input.split(',')

        if len(parts) != 3:
            print("Invalid syntax")
            continue

        try:
            coords = tuple(float(x) for x in parts)
            return coords

        except ValueError:
            for x in parts:
                try:
                    float(x.strip())
                except ValueError:
                    clean_x = x.strip()
                    print(f"Error on parameter '{clean_x}': could not convert string to float: '{clean_x}'")
                    break


def calculate_distance(p1, p2=(0, 0, 0)):
    return math.sqrt((p2[0] - p1[0])**2 + (p2[1] - p1[1])**2 + (p2[2] - p1[2])**2)

def main():
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
    print(f"Distance between the 2 sets of coordinates: {round(dist_between, 4)}")


if __name__ == "__main__":
    main()
