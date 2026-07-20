import sys
import typing


def get_user_input(prompt: str) -> str:
    sys.stdout.write(prompt)
    sys.stdout.flush()
    return sys.stdin.readline().strip()


def process_file(file: typing.TextIO) -> list[str]:
    processed_lines = []
    print("---")
    for line in file:
        modified_line = line.rstrip('\n') + "#"
        processed_lines.append(modified_line + "\n")
        print(modified_line)
    print("---")
    return processed_lines


def ft_archive_creation(file_path: str) -> None:
    print("=== Cyber Archives Recovery & Preservation ===")
    f = None
    try:
        f = open(file_path, "r")
        print(f"Accessing file '{file_path}'")
        modified_content = process_file(f)
        f.close()
        print(f"File '{file_path}' closed.")

        save_path = get_user_input("Enter new file name (or empty): ")

        if save_path:
            print(f"Saving data to '{save_path}'")
            dest = None
            try:
                dest = open(save_path, "w")
                dest.writelines(modified_content)
                print(f"Archive saved to '{save_path}'.")
                print("Archives secured. Preservation protocol complete.")
            except Exception as e:
                print(
                    f"Error opening file '{save_path}': {e}\n"
                )
                print("Data not saved")
            finally:
                if dest:
                    dest.close()
        else:
            print("No save path provided. Preservation aborted.")

    except Exception as e:
        print(f"[STDERR] Error opening file '{file_path}': {e}\n")
    finally:
        if f:
            f.close()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: ft_stream_management.py <file>\n")
    else:
        ft_archive_creation(sys.argv[1])
