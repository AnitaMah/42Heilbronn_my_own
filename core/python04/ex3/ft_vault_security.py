import sys
import typing


def get_user_input(prompt: str) -> str:
    sys.stdout.write(prompt)
    sys.stdout.flush()
    return sys.stdin.readline().strip()


def secure_archive(
    file_name: str,
    action: typing.Union[int, str] = 'read',
    content: str = ""
) -> typing.Tuple[bool, str]:

    is_write = (action == 1 or action == 'write')

    try:
        if is_write:
            with open(file_name, 'w') as f:
                f.write(content)
            return (True, 'Content successfully written to file')
        else:
            with open(file_name, 'r') as f:
                return (True, f.read())
    except Exception as e:
        return (False, str(e))


def main() -> None:
    print("=== Cyber Archives Security ===")

    print("Using 'secure_archive' to read from a nonexistent file:")
    print(secure_archive("/not/existing/file"))

    print("Using 'secure_archive' to read from an inaccessible file:")
    print(secure_archive("/etc/master.passwd"))

    filename = get_user_input("Enter file to read: ")
    if filename:
        result = secure_archive(filename, 'read')
        print(result)


if __name__ == "__main__":
    main()
