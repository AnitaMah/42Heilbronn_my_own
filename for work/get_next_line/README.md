`get_next_line project by anmakhov`

# get_next_line

## 📖 Description

`get_next_line` is a function that reads a line from a file descriptor and returns it.

Each call returns the next line from the file, including the `\n` character if present.

The function is designed to work with:
- files
- standard input
- any valid file descriptor

---

## ⚙️ Function Prototype

```c
char *get_next_line(int fd);
```

---

## 📦 Features

- Reads one line at a time
- Works with any file descriptor
- Handles multiple calls correctly
- Supports different buffer sizes (`BUFFER_SIZE`)
- Memory-safe (no leaks if implemented correctly)

---

## 🧠 How it works

- Reads data from file using `read()`
- Stores leftover data between calls
- Returns line until `\n` or EOF
- Keeps static buffer for each file descriptor

---

## 📁 Project Structure

```text
.
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
└── Makefile
```

---

## 🛠 Compilation

Compile with:

```bash
make
```

Or with buffer size:

```bash
cc -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

---

## 💡 Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

---

## 📌 Return Value

| Return | Meaning |
|--------|--------|
| Line | A line ending with `\n` or EOF |
| NULL | End of file or error |

---

## 🧩 Key Concepts

- Static variables
- File descriptors
- Memory allocation
- Buffer management
- Reading with `read()`

---

## 🚀 Allowed Functions

- `read`
- `malloc`
- `free`

---

## 👩‍💻 Author

Anita Makhovyk
42 School Student
