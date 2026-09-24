import sys
import typing


def process_file(file: typing.IO[str]) -> None:
    data = file.read()
    print("---\n")
    print(data, end="")
    print("\n---")


def ft_ancient_text(file_path: str) -> None:
    print("=== Cyber Archives Recovery ===")
    print(f"Accessing file '{file_path}'")
    f: typing.IO[str] | None = None
    try:
        f = open(file_path, "r")
        process_file(f)
    except Exception as e:
        print(f"Error opening file '{file_path}': {e}")
    finally:
        if f:
            f.close()
            print(f"File '{file_path}' closed.")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: ft_ancient_text.py <file>")
    else:
        ft_ancient_text(sys.argv[1])
