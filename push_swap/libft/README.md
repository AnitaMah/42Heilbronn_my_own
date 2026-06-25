*This project has been created as part of the 42 curriculum by anmakhov.*

# libft

> My own implementation of a subset of the C standard library, written from scratch as part of the 42 School curriculum.

---

## About

**libft** is a custom C library that reimplements common standard library functions — character checks, string manipulation, memory operations, and more. It also includes bonus linked list utilities and extra functions not found in the standard library.

The library is compiled into a static archive `libft.a` that can be linked into any future 42 project.

---

## Structure

```
libft/
├── libft.h          # Header with all function prototypes
├── Makefile         # Build rules
├── ft_is*.c         # Character classification
├── ft_str*.c        # String functions
├── ft_mem*.c        # Memory functions
├── ft_put*_fd.c     # Output functions
├── ft_lst*.c        # Linked list
└── ft_*.c           # Additional utilities
```

---

## Functions

### Part 1 — Character Classification & Conversion

| Function | Description |
|---|---|
| `ft_isalpha` | Check if character is alphabetic |
| `ft_isdigit` | Check if character is a decimal digit |
| `ft_isalnum` | Check if character is alphanumeric |
| `ft_isascii` | Check if character is in ASCII range (0–127) |
| `ft_isprint` | Check if character is printable |
| `ft_toupper` | Convert lowercase letter to uppercase |
| `ft_tolower` | Convert uppercase letter to lowercase |

### Part 2 — String Operations

| Function | Description |
|---|---|
| `ft_strlen` | Compute length of a string |
| `ft_strchr` | Locate first occurrence of character in string |
| `ft_strrchr` | Locate last occurrence of character in string |
| `ft_strncmp` | Compare two strings up to `n` characters |
| `ft_strlcpy` | Copy string with size limit (NUL-safe) |
| `ft_strlcat` | Concatenate strings with size limit (NUL-safe) |
| `ft_strdup` | Duplicate a string (allocates memory) |
| `ft_strnstr` | Find substring within a length-limited string |
| `ft_substr` | Extract substring from a string |
| `ft_strjoin` | Concatenate two strings into a new one |
| `ft_strtrim` | Trim specified characters from both ends of string |
| `ft_split` | Split string by delimiter into array of strings |
| `ft_strmapi` | Apply function to each character, returning new string |
| `ft_striteri` | Apply function to each character in-place (with index) |

### Part 3 — Memory Operations

| Function | Description |
|---|---|
| `ft_memset` | Fill memory area with a byte value |
| `ft_bzero` | Zero out a memory area |
| `ft_memcpy` | Copy memory area (no overlap handling) |
| `ft_memmove` | Copy memory area (handles overlap) |
| `ft_memchr` | Locate byte in memory area |
| `ft_memcmp` | Compare two memory areas |
| `ft_calloc` | Allocate zero-initialized memory |

### Part 4 — Conversion

| Function | Description |
|---|---|
| `ft_atoi` | Convert string to integer |
| `ft_itoa` | Convert integer to string (allocates memory) |

### Part 5 — Output (File Descriptor)

| Function | Description |
|---|---|
| `ft_putchar_fd` | Write a character to a file descriptor |
| `ft_putstr_fd` | Write a string to a file descriptor |
| `ft_putendl_fd` | Write a string followed by newline to a file descriptor |
| `ft_putnbr_fd` | Write an integer to a file descriptor |

### Part 6 — Linked List (Bonus)

| Function | Description |
|---|---|
| `ft_lstnew` | Create a new list node |
| `ft_lstadd_front` | Add node at the beginning of a list |
| `ft_lstsize` | Count nodes in a list |
| `ft_lstlast` | Get the last node of a list |
| `ft_lstadd_back` | Add node at the end of a list |
| `ft_lstdelone` | Delete a single node (with custom delete function) |
| `ft_lstclear` | Delete all nodes in a list |
| `ft_lstiter` | Apply function to each node's content |
| `ft_lstmap` | Apply function to each node, returning a new list |

---

## Build

```bash
# Compile the library
make

# Clean object files
make clean

# Clean everything including the archive
make fclean

# Rebuild from scratch
make re
```

This produces `libft.a` in the project root.

---

## Usage

Include the header and link the archive when compiling your project:

```c
#include "libft.h"
```

```bash
gcc main.c -L. -lft -o my_program
```

---

## AI Usage

This project used AI assistance (Claude by Anthropic and  ChatGPT) for the following tasks:

- **Debugging** — identifying issues in function implementations (e.g. `ft_memcpy` NULL behavior) and suggesting fixes
- **Code comments** — generating documentation comments for all function prototypes in `libft.h`
- **README** — generating this README file
