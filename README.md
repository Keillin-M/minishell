# 🐚 minishell

Rebuilding the shell... one prompt at a time.

Welcome to **minishell** — a 42 core project where you recreate a simplified version of the Unix Bash shell. You’ll learn how shells work from the inside out: parsing commands, handling signals, managing processes, implementing redirections, and more.

---

## 🚀 Project Overview

**minishell** is a major milestone in the 42 curriculum.

Goal: create a working shell that mimics the behavior of Bash — but built entirely from scratch in C.

You’ll handle things like:

```bash
echo hello | grep h > file.txt
```

🌐 Parse commands & arguments
🔗 Handle pipes and redirections
🧠 Manage environment and variables
⚙️ Implement built-ins like `cd`, `export`, `exit`
🚫 Handle signals (Ctrl+C, Ctrl+D, etc.) gracefully

---

## 📚 How It Works

When you launch **minishell**, it does the following:

1. Displays a custom prompt.
2. Reads user input line.
3. Parses and splits input (taking quotes, pipes, and redirections into account).
4. Executes built-in or external commands.
5. Manages environment variables, file descriptors, and child processes.
6. Waits for completion and loops again — until `exit`.

A simple command like:

```bash
ls -la | grep minishell > output.txt
```

Will internally be parsed, piped, and redirected manually using system calls.

---

## 🧠 Key Concepts Covered

* Lexing & parsing shell input (tokenization, quotes, operators)
* Command execution (built-ins vs `execve`)
* Pipes and redirections (`|`, `>`, `<`, `>>`, `<<`)
* Signal handling (`SIGINT`, `SIGQUIT`)
* Environment variables (with `env`, `export`, `unset`)
* Built-in commands (`cd`, `pwd`, `echo`, etc.)
* Process control (forking, waiting, exit statuses)
* Error handling and edge case coverage
* Memory management & cleanup

---

## 🛠️ Technologies

* **Language:** C
* **System Calls:** `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `open`, `close`, `read`, `write`, `signal`
* **Tools:** Makefile, GNU readline, Valgrind
* **OS:** Linux

---

## ⚙️ Built-In Commands

These are implemented **without** external binaries:

* `echo`
* `cd`
* `pwd`
* `export`
* `unset`
* `env`
* `exit`

They behave just like their Bash counterparts, including proper error messages and status codes.

---

## 📦 How to Use

Clone the repository:

```bash
git clone https://github.com/your-username/minishell.git
cd minishell
```

Build the project:

```bash
make
```

Run the shell:

```bash
./minishell
```

✅ Example usage:

```bash
minishell$ echo "Hello, minishell!"
minishell$ export VAR=test
minishell$ echo $VAR
minishell$ ls -l | grep .c > list.txt
minishell$ cat list.txt
```

---

## ✨ Bonus Features

* 🧾 **Here-Doc** support (`<<`)
* 🎨 Better prompt UI with readline
* 🛠️ Command history
* 🧼 Signal handling with edge cases
* 💬 Quote and escape character handling (`"`, `'`, `\`)

---

## 🧪 Example Workflow

```bash
minishell$ echo -e "one\ntwo\nthree" > numbers.txt
minishell$ cat numbers.txt | grep o | wc -l
2
minishell$ export NAME=42
minishell$ echo "Hello $NAME!"
Hello 42!
```

---

## 💡 Lessons Learned

* Tokenizing and parsing are *way* more complex than they look.
* Proper signal handling is essential for UX.
* Writing a shell makes you respect how much Bash does for you.
* Edge cases are everywhere — quoting, escaping, variable expansion...
* Clean memory management is a full-time job.

---

## 📁 Project Structure

```bash
src/
│
├── builtins/        # Implementation of shell built-ins
├── exec/            # Command execution, fork/exec
├── minishell/       # Entry point, shell loop
├── parser/          # Syntax tree, redirections, pipes
├── redirections/    # Redirection variable management
├── signals/         # Signal handling
├── token/           # Tokenization logic
└── utils/           # Signal handling
```

---

## 📜 Mandatory Rules

* Only allowed to use `readline`
* No memory leaks or zombie processes
* Exit codes must match Bash behavior
* Handle `Ctrl+C`, `Ctrl+\`, and `Ctrl+D` correctly

## 🙌 Credits
- Created as part of the 42 School curriculum.
- Group project with @HeartThanakorn
