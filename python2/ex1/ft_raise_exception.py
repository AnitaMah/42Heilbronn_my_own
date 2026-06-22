def ft_raise_exception(temp_str)->None:
    try:
        temp_int = int(temp_str)
        if  not (0 <= temp_str <= 40):
            raise ValueError(f"Temperature is now {temp_int}")
        print(f"Caught input_temperature error: {temp_int}°C is too hot for plants (max 40°C)")
    except ValueError:
        print(f"Caught input_temperature error: invalid literal for int() with base 10: 'abc'")
