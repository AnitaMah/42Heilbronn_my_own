def open_non_created_file() -> None:
    open("/non/existent/file", "r")


def divisions_error() -> None:
    1 / 0


def garden_operations(operation_number: int) -> None:
    if operation_number == 0:
        print("Testing operation 0...")
        int("abc")
    elif operation_number == 1:
        print("Testing operation 1...")
        divisions_error()
    elif operation_number == 2:
        print("Testing operation 2...")
        open_non_created_file()
    elif operation_number == 3:
        print("Testing operation 3...")
        "string" + 7
    else:
        print(f"Testing operation {operation_number}...")


def test_error_types() -> None:
    print("=== Garden Error Types Demo ===")

    for i in range(5):
        try:
            garden_operations(i)
            print("Operation completed successfully")
        except ValueError as e:
            print(f"Caught ValueError: {e}")
        except ZeroDivisionError as e:
            print(f"Caught ZeroDivisionError: {e}")
        except FileNotFoundError as e:
            print(f"Caught FileNotFoundError: {e}")
        except TypeError as e:
            print(f"Caught TypeError: {e}")

    print()
    print("All error types tested successfully!")


if __name__ == "__main__":
    test_error_types()
