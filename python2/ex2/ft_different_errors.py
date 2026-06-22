def open_non_created_file():
        open("non_create.txt", "r")

def divisions_error():
    1 / 0

def garden_operations(operation_number):
    if operation_number == 0:
        print("Testing operation 0...")
        int ("abc")
    elif operation_number == 1:
         print("Testing operation 1...")
         divisions_error()
    elif operation_number == 2:
         print("Testing operation 2...")
         open_non_created_file()
    elif operation_number == 3:
         print("Testing operation 3...")
         "string" + 7

def test_error_types():
     print("=== Garden Error Types Demo ===")
     for i in range(4):
        try:
            print(f"Testing of garden_operations")
            garden_operations(i)
        except ValueError:
            print("Caught ValueError: invalid literal for int() with base 10: 'abc'")
        except ZeroDivisionError:
            print("Caught ZeroDivisionError: division by zero")
        except FileNotFoundError:
            print("Caught FileNotFoundError: [Errno 2] No such file or directory: '/non/existent/file'")
        except TypeError:
            print("Caught TypeError: can only concatenate str (not \"int\") to str")
        print("Operation completed successfullys")
     print("All error types tested successfully!")

if __name__ == "__main__":
    test_error_types()
