import sys
import typing


def get_user_input(prompt: str) -> str:
    sys.stdout.write(prompt)
    sys.stdout.flush()
    line = sys.stdin.readline()
    if line.endswith("\n"):
        line = line[:-1]
    return line


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
        sys.stderr.write(f"[STDERR] Error opening file '{file_path}': {e}\n")
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
    sys.stdout.flush()
    f: typing.IO[str] | None = None
    try:
        f = open(file_path, "w")
        f.write(data)
        print(f"Data saved in file '{file_path}'.")
    except Exception as e:
        sys.stderr.write(f"[STDERR] Error opening file '{file_path}': {e}\n")
        sys.stderr.flush()
        print("Data not saved.")
    finally:
        if f:
            f.close()


def ft_stream_management(file_path: str) -> None:
    print("=== Cyber Archives Recovery & Preservation ===")
    sys.stdout.flush()
    data = read_archive(file_path)
    if data is None:
        return
    new_data = transform(data)
    print("\nTransform data:")
    print("---\n")
    print(new_data, end="")
    print("\n---")
    save_path = get_user_input("Enter new file name (or empty): ")
    if save_path:
        save_archive(save_path, new_data)
    else:
        print("Not saving data.")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.stderr.write("Usage: ft_stream_management.py <file>\n")
    else:
        try:
            ft_stream_management(sys.argv[1])
        except KeyboardInterrupt:
            sys.stderr.write("\n[STDERR] Input aborted.\n")
