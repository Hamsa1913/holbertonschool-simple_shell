# C - Simple Shell.

The Goal - Building a simple shell that listens, understands and run commands.

## About GitHub:
This project created in a one repository called holbertonschool-simple_shell. As a joint project
both Mariam Almaleki and Hamsah worked directly on the main with no branches. 
## GitHub link: 

## Appendix

This README.md file will explian the process of building a simple shell in two main parts:

1- The 7 Phases to bulid a simple shell (conceptually).

2- The purpose of each file in the simple shell project (practically).

## PART 1: Phases of Building a Simple Shell:

Think of the shell as a pipeline that repeats forever:
```bash
  Prompt → Read → Parse → Resolve → Execute → Wait → Cleanup → Repeat
```
## Phase 1: Shell startup
- Goal: Decide how the shell behaves.

- What happens: 
Check if input comes from:
```bash
Terminal → interactive mode → show $

Pipe / file → non-interactive → NO prompt
```
- Why this matters:
Interactive shells print prompts.
Non-interactive shells must be silent.

- Key functions: 
```bash
isatty(STDIN_FILENO)
```
## Phase 2: Read user input
- Goal: Get a full command line safely.

- What happens:
Use getline() to read the entire line.
Handle: both Newline removal and Empty lines

- Why this matters:
getline handles any length input safely.
Empty input should do nothing, not crash or fork.

- Key functions:
```bash
getline(&line, &len, stdin)
```
## Phase 3: tokenize the input
- Goal: Turn a string into argv[]
Example Input:
```bash
ls -l /tmp
```
Output:
```bash
argv[0] = "ls"
argv[1] = "-l"
argv[2] = "/tmp"
argv[3] = NULL
```
- Why this matters:
execve only understands arrays.

- Important points:
Never leak memory.
Always NULL-terminate argv.

## Phase 4: PATH handling
- Goal: Convert a command name into an absolute executable path. Example:

```bash
ls → /bin/ls
```

- Critical rules (from Holberton checker):
✔ If PATH is empty → command NOT found
✔ If PATH is missing → command NOT found
✔ If command has / → do NOT search PATH
✔ If command does not exist → do NOT fork


## Phase 5: Execute the command (fork + execve)
- Goal:
Run the program in a child process.

- What happens:
Parent calls fork()
Child calls execve()
Parent waits

- Why this matters:
Shell must stay alive.
Command must run in child.

- Important Points:
If execve fails → exit child
Parent always waits


## Phase 6: Error handling
- Goal:
Behave like a real shell.


## Phase 7: tokenize the input
- Goal:
Free memory and repeat safely.

- What happens:
Free argv → Free allocated paths → Free input buffer on exit.

- Why this matters:
Long-running shell stability

## PART 2: Purpose of Each File in the Simple Shell

| File Name           | Purpose                         | Description |
|---------------------|----------------------------------|-------------|
| `main.c`            | Program entry point              | Contains the `main` function. Initializes the shell and starts the main loop. |
| `hsh.c`             | Shell core logic                 | Implements the main shell loop: prompt, input reading, command parsing, execution, and cleanup. |
| `path.c`            | PATH command resolution          | Searches for executable commands in the directories listed in the `PATH` environment variable. |
| `split_line.c`      | Command parsing                  | Splits the input line into an array of arguments (`argv`). |
| `utils.c`           | Helper utilities                 | Contains utility functions such as memory helpers and string operations. |
| `simple_shell.h`    | Header file                      | Contains function 
