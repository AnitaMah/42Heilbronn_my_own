"""!
@file ft_command_quest.py
@brief Display the command-line arguments received by the script.
"""
import sys


def main() -> None:
    """!
    @brief Print the program name and every command-line argument.
    @return None.
    """
    print("=== Command Quest ===")
    print(f"Program name: {sys.argv[0]}")
    len_of_argv = len(sys.argv) - 1

    if len_of_argv == 0:
        print("No arguments provided!")
    else:
        print(f"Arguments received: {len_of_argv}")

        iter = 1
        while iter <= len_of_argv:
            print(f"Argument {iter}: {sys.argv[iter]}")
            iter += 1
    print(f"Total arguments: {len(sys.argv)}")


if __name__ == "__main__":
    main()
