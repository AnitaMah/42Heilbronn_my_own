import sys


def main()->None:
    print()
    len_of_argv = len(sys.argv) - 1

    if len_of_argv == 0:
        print("No arguments provided!")
    else:
        print(f"Arguments received: {len_of_argv}")

        iter = 1
        while iter <= len_of_argv:
            print(f"Argument 1: {sys.argv[iter]}")
            iter += 1
    print(f"Total arguments: {len(sys.argv)}")

if __name__ == "__main__":
    main()
