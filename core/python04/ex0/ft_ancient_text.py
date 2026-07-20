import sys
import typing


def process_file(file: typing.TextIO) -> None:
    data = file.read()
    print(data)


def ft_ancient_text(file_path: str) -> None:
    print("=== Cyber Archives Recovery ===")
    f = None
    try:
        f = open(file_path, "r")
        print(f"Accessing file '{file_path}'")
        process_file(f)

    except FileNotFoundError:
        print(
            f"Error opening file '{file_path}': [Errno 2] "
            f"No such file or directory: '{file_path}'\n"
        )
    except PermissionError:
        print(f"Accessing file '{file_path}'")
        print(
            f"Error opening file '{file_path}': [Errno 13] "
            f"Permission denied: '{file_path}'\n"
        )
    finally:
        if f:
            f.close()
            print(f"File '{file_path}' closed.")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: ft_ancient_text.py <file>\n")
    else:
        ft_ancient_text(sys.argv[1])
