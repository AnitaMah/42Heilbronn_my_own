def input_temperature(temp_str)->None:
    try:
        temp_int = int(temp_str)
        print(f"Temperature is now {temp_int}")
    except ValueError:
        print(f"Caught input_temperature error: invalid literal for int() with base 10: 'abc'")
