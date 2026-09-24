import sys
import typing


def read_archive(file_path: str) -> str | None:
    print(f"Accessing file '{file_path}'")
    f: typing.IO[str] | None = None
    data: str | None = None
    try:
        f = open(file_path, "r")
        data = f.read()
        print("---\n")
        print(data, end="")
        print("\n---")
    except Exception as e:
        print(f"Error opening file '{file_path}': {e}")
    finally:
        if f:
            f.close()
            print(f"File '{file_path}' closed.")
    return data


def transform(data: str) -> str:
    lines = data.split("\n")
    if lines and lines[-1] == "":
        lines.pop()
    return "".join(line + "#\n" for line in lines)


def save_archive(file_path: str, data: str) -> None:
    print(f"Saving data to '{file_path}'")
    f: typing.IO[str] | None = None
    try:
        f = open(file_path, "w")
        f.write(data)
        print(f"Data saved in file '{file_path}'.")
    except Exception as e:
        print(f"Error opening file '{file_path}': {e}")
        print("Data not saved.")
    finally:
        if f:
            f.close()


def ft_archive_creation(file_path: str) -> None:
    print("=== Cyber Archives Recovery & Preservation ===")
    data = read_archive(file_path)
    if data is None:
        return
    new_data = transform(data)
    print("\nTransform data:")
    print("---\n")
    print(new_data, end="")
    print("\n---")
    save_path = input("Enter new file name (or empty): ")
    if save_path:
        save_archive(save_path, new_data)
    else:
        print("Not saving data.")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: ft_archive_creation.py <file>")
    else:
        try:
            ft_archive_creation(sys.argv[1])
        except (EOFError, KeyboardInterrupt):
            print("\nInput aborted. Not saving data.")
