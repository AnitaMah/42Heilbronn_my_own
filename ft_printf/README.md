`ft_printf 42 School project developed by anmakhov`

# ft_printf

A custom implementation of the standard C `printf()` function developed as part of the 42 School curriculum.

## Description

The purpose of this project is to recreate the behavior of the original `printf` function while learning how variadic functions work in C.

The function handles multiple format specifiers and returns the number of printed characters, just like the original `printf`.

## Supported Conversions

| Conversion | Description |
|------------|-------------|
| `%c` | Character |
| `%s` | String |
| `%p` | Pointer address |
| `%d` | Decimal integer |
| `%i` | Integer |
| `%u` | Unsigned integer |
| `%x` | Hexadecimal (lowercase) |
| `%X` | Hexadecimal (uppercase) |
| `%%` | Percent sign |

## Project Structure

```text
.
├── ft_printf.c
├── ft_printf.h
├── ft_print_char.c
├── ft_print_str.c
├── ft_print_nbr.c
├── ft_print_unsigned.c
├── ft_print_hex.c
├── ft_print_ptr.c
├── Makefile
└── README.md
```

## Compilation

Build the static library:

```bash
make
```

This creates:

```bash
libftprintf.a
```

Available rules:

```bash
make
make clean
make fclean
make re
```

## Usage

Include the header file:

```c
#include "ft_printf.h"
```

Compile your program:

```bash
cc main.c libftprintf.a
```

Example:

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("Hello %s!\n", "42");
	ft_printf("Number: %d\n", 42);
	ft_printf("Hexadecimal: %x\n", 42);
	return (0);
}
```

Output:

```text
Hello 42!
Number: 42
Hexadecimal: 2a
```

## Return Value

`ft_printf()` returns the number of characters printed.

Example:

```c
int	len;

len = ft_printf("Hello\n");
```

`len` will contain:

```text
6
```

## Concepts Learned

- Variadic functions
- `stdarg.h`
- `va_start`
- `va_arg`
- `va_end`
- Integer conversion
- Hexadecimal conversion
- Pointer formatting
- Static libraries
- Makefiles

## Allowed Functions

- malloc
- free
- write
- va_start
- va_arg
- va_copy
- va_end

## Author

Anita Makhovyk

42 School Student
