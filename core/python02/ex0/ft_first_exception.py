def input_temperature(temp_str: str) -> int:
    """Convert a temperature reading string to an integer."""
    return int(temp_str)


def test_temperature() -> None:
    print("=== Garden Temperature ===")

    test_values = ["25", "abc"]
    for value in test_values:
        print(f"\nInput data is '{value}'")
        try:
            temp_int = input_temperature(value)
            print(f"Temperature is now {temp_int}°C")
        except ValueError as e:
            print(f"Caught input_temperature error: {e}")

    print("\nAll tests completed - program didn't crash!")


if __name__ == "__main__":
    test_temperature()
