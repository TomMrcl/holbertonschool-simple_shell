# 🐚 Simple Shell

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Standard](https://img.shields.io/badge/Standard-GNU89-orange.svg)
![Style](https://img.shields.io/badge/Betty-Approved-brightgreen.svg)
![Project](https://img.shields.io/badge/Project-Holberton-success.svg)

> A minimalist UNIX command line interpreter written in **C**, inspired by `/bin/sh`.

---

## 📋 Table of Contents

- [Description](#-description)
- [Features](#-features)
- [Compilation](#%EF%B8%8F-compilation)
- [Usage](#-usage)
- [Built-in Commands](#-built-in-commands)
- [Project Structure](#-project-structure)
- [Error Handling](#%EF%B8%8F-error-handling)
- [Testing](#-testing)
- [Examples](#-examples)
- [Authors](#-authors)

---

## 📖 Description

**Simple Shell** is a basic UNIX command line interpreter developed as part of the **Holberton School** curriculum. The project aims to understand how a shell works internally by implementing core functionalities such as:

- Process creation using `fork()`
- Command execution with `execve()`
- Environment management
- PATH resolution
- Memory management
- Error handling

The shell supports both **interactive** and **non-interactive** modes and behaves similarly to `/bin/sh` for basic commands.

---

## 🚀 Features

- ✅ Interactive and non-interactive shell modes
- ✅ Command execution using `fork` and `execve`
- ✅ PATH environment variable handling
- ✅ Command arguments support
- ✅ Environment variables handling
- ✅ Built-in commands (`exit`, `env`)
- ✅ Proper exit status management
- ✅ No memory leaks (Valgrind clean)
- ✅ Fork is not called when a command does not exist
- ✅ Handles `Ctrl + D` (EOF) gracefully

---

## ⚙️ Compilation

To compile the shell, use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### 🧹 Coding Style

This project strictly follows the **Betty** coding style.

To check your code against Betty:

```bash
betty *.c *.h
```

✔️ No warnings • ✔️ No errors • ✔️ Fully Betty compliant

---

## 🧪 Usage

### Interactive Mode

Run the shell in interactive mode:

```bash
./hsh
```

You'll see a prompt where you can type commands:

```bash
($) ls -l
($) /bin/pwd
($) env
($) exit
```

### Non-Interactive Mode

You can also pipe commands into the shell:

```bash
echo "ls -l /tmp" | ./hsh
```

Or execute commands from a file:

```bash
cat commands.txt | ./hsh
```

---

## 🔧 Built-in Commands

| Command | Description |
|---------|-------------|
| `exit` | Exit the shell |
| `env` | Print the current environment variables |

### Examples

```bash
($) exit
```

```bash
($) env
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin
HOME=/home/user
PWD=/home/user/simple_shell
...
```

---

## 📁 Project Structure

```
simple_shell/
│
├── main.c              # Entry point and main loop
├── execute.c           # Command execution logic
├── prompt.c            # Prompt display
├── read_command.c      # Input handling
├── utils_parse.c       # Command parsing utilities
├── utils_path.c        # PATH resolution
├── utils_env.c         # Environment handling
├── utils_exec.c        # Execution helpers
├── main.h              # Header file with function prototypes
├── man_1_simple_shell  # Manual page
├── AUTHORS             # Project contributors
└── README.md           # This file
```

---

## ⚠️ Error Handling

The shell implements robust error handling:

- Error messages closely match `/bin/sh` format
- Exit status **127** returned when a command is not found
- Handles empty input and extra spaces
- Proper handling of `Ctrl + D` (EOF)
- Graceful shell termination
- Displays appropriate error messages for invalid commands

### Example Error Output

```bash
($) /bin/nonexistent
./hsh: 1: /bin/nonexistent: not found
```

---

## 🧪 Testing

### Memory Leak Check

Use Valgrind to ensure there are no memory leaks:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./hsh
```

### Test Cases

```bash
# Test 1: Simple command
echo "ls" | ./hsh

# Test 2: Command with arguments
echo "ls -la /tmp" | ./hsh

# Test 3: Multiple commands
echo -e "pwd\nls\nenv" | ./hsh

# Test 4: Non-existent command
echo "nonexistent_command" | ./hsh

# Test 5: Built-in commands
echo -e "env\nexit" | ./hsh
```

---

## 💡 Examples

### Example 1: Basic Commands

```bash
($) ls
file1.c  file2.c  main.h  README.md
($) pwd
/home/user/simple_shell
```

### Example 2: Commands with Arguments

```bash
($) ls -l /tmp
total 12
drwxr-xr-x 2 user user 4096 Jan  7 10:30 test_dir
-rw-r--r-- 1 user user   42 Jan  7 10:31 test_file
```

### Example 3: Environment Variables

```bash
($) env
USER=student
HOME=/home/student
PATH=/usr/local/bin:/usr/bin:/bin
```

### Example 4: Exit

```bash
($) exit
$
```

---

## 👥 Authors

- **Your Name** - [GitHub Profile](https://github.com/yourusername)
- **Collaborator Name** - [GitHub Profile](https://github.com/collaborator)

---

## 📄 License

This project is part of the Holberton School curriculum.

---

## 🙏 Acknowledgments

- Holberton School for the project guidelines
- All peers and mentors who provided support
- The `/bin/sh` shell for inspiration

---

## 📚 Resources

- [Unix Shell - Wikipedia](https://en.wikipedia.org/wiki/Unix_shell)
- [execve man page](https://man7.org/linux/man-pages/man2/execve.2.html)
- [fork man page](https://man7.org/linux/man-pages/man2/fork.2.html)
- [Betty Style Guide](https://github.com/holbertonschool/Betty)

---

**Made with ❤️ by Holberton School students**