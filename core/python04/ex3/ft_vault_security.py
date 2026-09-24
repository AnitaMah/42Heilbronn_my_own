def secure_archive(
    file_name: str,
    action: str = "read",
    content: str = ""
) -> tuple[bool, str]:
    try:
        if action == "write":
            with open(file_name, "w") as f:
                f.write(content)
            return (True, "Content successfully written to file")
        if action == "read":
            with open(file_name, "r") as f:
                return (True, f.read())
        return (False, f"Unknown action '{action}'")
    except Exception as e:
        return (False, str(e))


def main() -> None:
    print("=== Cyber Archives Security ===\n")

    print("Using 'secure_archive' to read from a nonexistent file:")
    print(secure_archive("/not/existing/file"))

    print("\nUsing 'secure_archive' to read from an inaccessible file:")
    print(secure_archive("/etc/shadow"))

    print("\nUsing 'secure_archive' to read from a regular file:")
    result = secure_archive("ancient_fragment.txt")
    print(result)

    print("\nUsing 'secure_archive' to write previous content to a new file:")
    if result[0]:
        print(secure_archive("new_fragment.txt", "write", result[1]))
    else:
        print("(skipped: nothing to write)")


if __name__ == "__main__":
    main()
