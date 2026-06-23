*This project has been created as part of the 42 curriculum by arsokolo.*

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
|--------|---------|
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
## 🤖 AI Resources & Usage

### Overview
This section documents how AI can assist in understanding, debugging, and optimizing the `get_next_line` project. AI tools are valuable for learning, code review, and problem-solving.

### Learning & Understanding
**Use AI for:**
- **Conceptual explanations**: Ask about how static variables work in C or file descriptor management
- **Visual diagrams**: Generate flowcharts of the `get_next_line` algorithm
- **Step-by-step walkthroughs**: Understand the buffer management process
- **C fundamentals**: Review memory allocation, pointer arithmetic, or string handling

**Example prompts:**
```
"Explain how static variables maintain state between function calls in get_next_line"
"Create a flowchart of the get_next_line algorithm"
"What are the common pitfalls when managing file descriptors?"
```

### Debugging & Problem-Solving
**Use AI for:**
- **Memory leak analysis**: Get help understanding valgrind output
- **Edge case identification**: Discover edge cases (empty files, very long lines, multiple FDs)
- **Segmentation fault troubleshooting**: Debug crashes without giving full code
- **Behavior validation**: Understand expected behavior in specific scenarios

**Example prompts:**
```
"My program crashes when reading from stdin. What could cause this in get_next_line?"
"How do I handle files larger than BUFFER_SIZE?"
"What edge cases should I test?"
```

### Code Review & Optimization
**Use AI for:**
- **Code quality feedback**: Ask for suggestions on structure and efficiency
- **Best practices**: Learn C conventions for this type of implementation
- **Performance tips**: Understand BUFFER_SIZE tradeoffs
- **Security concerns**: Identify potential vulnerabilities

**Example prompts:**
```
"Review my get_next_line implementation for memory leaks (share 20 lines of code)"
"How does BUFFER_SIZE affect performance?"
"Are there any security issues I should be aware of?"
```

### Testing & Validation
**Use AI for:**
- **Test case generation**: Get comprehensive test scenarios
- **Test input creation**: Generate tricky test files (empty lines, no newline at EOF, etc.)
- **Expected behavior**: Clarify how function should behave in edge cases

**Example prompts:**
```
"Generate 10 edge case test scenarios for get_next_line"
"Create a test file with multiple empty lines and no newline at EOF"
"Should get_next_line preserve the newline character?"
```

### Bonuses & Advanced Topics
**Use AI for:**
- **Bonus feature exploration**: Ideas for extending functionality
- **Performance analysis**: How to optimize for speed vs memory
- **File descriptor limits**: Understanding system constraints
- **Error handling strategies**: Best practices for robust implementation

**Example prompts:**
```
"What are interesting bonus features for get_next_line?"
"How can I handle reading from multiple file descriptors efficiently?"
"What's the theoretical limit for BUFFER_SIZE?"
```

### Best Practices for Using AI

1. **Share snippets, not whole projects**
   - Good: Share 10-20 lines for specific review
   - Avoid: Pasting entire implementation at once

2. **Be specific with questions**
   - Good: "Why does my code fail with empty files?"
   - Avoid: "My code doesn't work"

3. **Verify AI suggestions**
   - Always test recommendations before using them
   - Cross-reference with C documentation
   - Ask follow-up questions if unclear

4. **Use AI as a learning tool**
   - Don't just copy-paste solutions
   - Ask "why" to deepen understanding
   - Work through suggestions step-by-step

5. **Respect project guidelines**
   - Use AI for learning and debugging, not cheating
   - Follow your school/institution's academic integrity policies
   - Focus on understanding, not just getting code that works

### Recommended Workflows

**For getting unstuck:**
1. Describe the problem you're facing
2. Ask for conceptual guidance (not code)
3. Ask clarifying questions to deepen understanding
4. Implement the solution yourself

**For optimization:**
1. Share a small code snippet
2. Ask for efficiency feedback
3. Request explanation of suggestions
4. Test and measure improvements

**For debugging:**
1. Describe the symptom (crash, wrong output, memory leak)
2. Show error messages or valgrind output
3. Ask about possible causes
4. Implement and test fix

---
## 📚 Additional Resources

- **C File I/O**: POSIX `read()` man pages, file descriptor concepts
- **Memory Management**: Understanding malloc/free, valgrind for leak detection
- **Static Variables**: How they maintain state across function calls
- **Buffer Management**: Circular buffers, static allocation strategies
- **Testing**: Creating comprehensive test files and test harnesses
- **Guide form https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line and https://medium.com/@lannur-s/gnl-c3cff1ee552b.
- **Also I had use guide from Claude and ChatGPT

---
## 📝 Notes
- This project emphasizes understanding low-level C concepts
- Focus on memory management and clean code
- Test thoroughly with edge cases
- Don't hesitate to ask for help understanding concepts
- Use AI as a learning partner, not a shortcut

---
**Author**: anmakhov
**Last Updated**: 2026
