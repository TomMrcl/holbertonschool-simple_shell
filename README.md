# 🐚 Simple Shell

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Standard](https://img.shields.io/badge/Standard-GNU89-orange.svg)
![Style](https://img.shields.io/badge/Betty-Approved-brightgreen.svg)
![Status](https://img.shields.io/badge/Project-Holberton-success.svg)

> A minimalist UNIX command line interpreter written in **C**, inspired by `/bin/sh`.

---

## 📌 Language
- **C (GNU89)**

---

## 📖 Project Description
**Simple Shell** is a basic UNIX command line interpreter developed as part of the  
**Holberton School** curriculum.

The objective of this project is to understand how a shell works internally by
reimplementing its core mechanisms, including:

- process creation
- command execution
- environment management
- PATH resolution
- memory management
- error handling

The shell supports both **interactive** and **non-interactive** modes and behaves
similarly to `/bin/sh` for basic commands.

---

## ⚙️ Compilation
Compile the shell using `gcc` with the following flags:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
🧹 Coding Style & Betty
This project strictly follows the Betty coding style.

To verify coding style and documentation locally:

bash
Copier le code
./Betty/betty.sh *.c *.h
✔️ No warnings
✔️ No errors
✔️ Fully Betty compliant

🚀 Features Implemented
The following features have been implemented throughout the project tasks:

Interactive shell loop

Non-interactive mode support

Command execution using fork and execve

PATH environment variable handling

Support for command arguments

Environment variables handling

Built-in commands

Proper exit status management

No memory leaks (Valgrind clean)

Fork is not called when a command does not exist

🔧 Built-in Commands
Command	Description
exit	Exit the shell
env	Print the current environment

⚠️ Error Handling
Error messages closely match /bin/sh

Exit status 127 returned when a command is not found

Handles empty input and extra spaces

Proper handling of Ctrl + D (EOF)

Graceful shell termination

📁 Project Structure
graphql
Copier le code
.
├── main.c              # Entry point and main loop
├── execute.c           # Command execution logic
├── prompt.c            # Prompt display
├── read_command.c      # Input handling
├── utils_parse.c       # Command parsing utilities
├── utils_path.c        # PATH resolution
├── utils_env.c         # Environment handling
├── utils_exec.c        # Execution helpers
├── main.h              # Header file
├── README.md           # Project documentation
└── man_hsh.1           # Manual page
🧪 Usage Examples
Interactive mode
bash
Copier le code
./hsh
($) ls -l
($) env
($) exit
Non-interactive mode
bash
Copier le code
echo "ls -l /tmp" | ./hsh