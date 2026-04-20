# TEAMX Shell Project
## Alexandria University - Faculty of Computers and Data Science

- **Team Number:** TEAMXX

### Team Members and role:
| Name                         | ID       | Role |
|------------------------------|----------|------|
| Mariam Khaled Ahmed         | 23011528 |      |
| Mariam Hafez Saed           | 23011150 |      |
| Sondos Yasser Mohammed      | 23010132 |      |
| Soheir Mohammed Salah       | 23010158 |      |
| Mariam Farag Mohammed       | 23011531 |      |
| Asmaa Abdallah Mosa         | 23011043 |      |
| Salma Essam Ismail          | 23011286 |      |
| Basmala Mahmoud El-Sayed    | 23010140 |      |
| Rania Ali Abo Zaid          | 23010113 |      |
| Shahd Waleed Bayoumy        | 23010091 |      |

### How to run:
1. Open Terminal in this folder.
2. Type `make`.
3. Run using `./myShell`.
# Module: Error Handler Module for myShell
- **Module Author:** Maryam Hafez Saed
- **Student ID:** 23011150
## Module Description 
This module handles all error conditions in the shell including:
- fork/exec/pipe failures
- file and directory errors
- command not found 
- permission denied 

## function
'print_error()' -> prints formatted error messages
'handle_fork_error()' -> handles fork() failures
'handle_exec_error()' -> handles exec() failures
'handle_pipe_error()' -> handles pipe() failures
'handle_file_error()' -> handles pipe operations errors
'handle_cd_error()' -> handles cd command errors
'handle_command_not_found()' -> handles unknown commands

## error codes
- 0: success
- 1: fork failed
- 2: exec failed
- 3: pipe failed
- 4: file not found
- 5: permission denied
- 6: directory not found
- 127: command not found

# Module: Command Line Parser
- **Author:** Mariam Khaled  
- **Student ID:** 23011528  

---

## 1. Module Overview
This module serves as the "brain" of **myShell**. It is responsible for taking raw user input and transforming it into a structured, executable format. By implementing a **Linked List** architecture, the parser can handle complex command sequences, including multiple pipes and background processes.

---

## 2. Key Features
- **Pipeline Support:** Splits commands using the `|` operator into a sequence of executable units.
- **I/O Redirection:** Automatically detects `<` for input and `>` for output redirection.
- **Background Execution:** Identifies the `&` symbol to run processes without blocking the shell.
- **Memory Safety:** Includes a dedicated cleanup mechanism to prevent memory leaks during long sessions.

---

## 3. Function Documentation

| Function | Description |
| :--- | :--- |
| `parse_pipes()` | The entry point; splits the input string into a Linked List of commands. |
| `parse_single_command()` | Analyzes individual commands to extract arguments and file paths. |
| `free_command_list()` | Recursively frees all heap-allocated memory for the command list. |

---


5. Development Roadmap
[x] Tokenization: Successful splitting of strings into individual tokens.

[x] Data Structure: Full implementation of the Linked List to support Pipes.

[x] Robustness: Seamless integration with error_handler.h for memory allocation failures.

[ ] Next Step: Implement logic to bypass fork() for built-in commands (cd, pwd, etc.).

[ ] Next Step: Final synchronization and stress-testing with the Execution engine.

---

# Module: Built-in Commands of the shell
- **Module Author:** Shahd Waleed Bayoumy
- **Student ID:** 23010091

---

## 1. Module Overview
This module is responsible for implementing the Built-in Commands of the shell. Unlike external programs, these commands are executed directly within the shell process itself to modify its state or environment (such as changing the current directory). By handling these internally, we avoid the overhead of creating new processes for basic shell operations.

---

## 2. Functions Specifications
### 1. shell_cd

Description: Changes the current working directory of the shell.
Implementation: It uses the chdir() system call to update the shell's execution path.
Importance: This is a critical built-in because a child process created by fork() cannot change the directory of its parent process.

### 2. shell_pwd

Description: Prints the absolute path of the current working directory.
Implementation: It utilizes the getcwd() function to retrieve and display the current path.
Importance: Provides users with their current location within the file system hierarchy.

### 3. shell_exit

Description: Terminates the shell session safely.
Implementation: Calls the exit() function to close the program and return control to the operating system.
Importance: Provides a formal and clean way for the user to close the shell.

### 4. execute_builtin

Description: A dispatcher function that checks if the entered command is a built-in or an external one.
Implementation: Compares the user input with the list of supported built-ins (cd, pwd, exit) before attempting to fork() for external commands.
Importance: Ensures that internal commands are prioritized and executed without using exec() family functions.

---

# Module: Execution (fork ,exec)
- **Module Author:** Basmala Mahmoud Elsayed 
- **Student ID:** 23010140

---
## 1. Module Overview
Execution Engine: Core execution using fork() + execvp() + waitpid()

## 2. My Contribution
I implemented the core execution layer (execution.c and execution.h):

Responsible for fork() and execvp() to run external commands.
Integrated built-in commands without using fork() (calls execute_builtin()).
Set up the global fg_pid for SIGINT (Ctrl+C) handling.

# Module: Pipeline Implementation

- **Module Author:** Sondos Yasser
- **Student ID:** 23010132

## 1. Module Overview
This module is responsible for the creation and management of inter-process communication (IPC) using Unix pipes. It allows the output of one command to serve as the input for the next, supporting complex command chains.

## 2. Core Functions & Implementation
implementing the pipeline logic in execution.c, focusing on these core functions:
    
    void execute_pipeline(struct Command *cmd_list):
        Logic: Iterates through a linked list of commands. For each command (except the last), it creates a pipe using pipe().
        Process Management: It uses fork() for every command in the pipeline to ensure parallel execution.
        I/O Linking: Inside the child process, it uses dup2() to redirect STDOUT to the "write end" of the current pipe and STDIN to the "read end" of the previous pipe.

## 3. Integration & Robustness
    With Redirection: The implementation is designed to honor file redirection even within pipes. For example, in cat < file.txt | grep "search", the first process correctly redirects its input from a file before passing data to the pipe.
    
	With Error Handling:
        It monitors pipe() and fork() system calls; if any fails, it invokes the error_handler to prevent shell crashes.
        It ensures all unused pipe file descriptors are closed in both parent and child processes to avoid resource leaks and "hanging" processes (zombies).

    Execution Flow: By managing file descriptors carefully, it ensures that commands like ls | grep .c | wc -l execute seamlessly, passing data through the kernel buffer without manual intervention.

### **Module: Shell Loop and Prompt (The REPL Engine)**

**Module Author:** Mariam Farag Mohammed 
**Student ID:** 23011531 
**Module Description:** 
This module serves as the primary interface and the central control loop of **myShell**. It implements the **REPL** (Read-Eval-Print Loop) pattern, coordinating the lifecycle of a command from user input to execution and memory cleanup.

**Key Responsibilities:**
-   **Interactive Prompt:** Displaying a persistent command-line interface.
-   **Input Management:** Capturing raw user input and handling End-of-File (EOF) signals.
-   **Pre-processing:** Cleaning input strings and filtering empty commands.
-   **Orchestration:** Sequencing the calls between the History, Parser, and Execution modules
-   **Memory Management:** Ensuring command structures are freed after each execution cycle to prevent memory leaks
**Functions:**
-   `main()` -> The entry point that hosts the infinite `while(1)` loop.
-   `fgets()` (Internal) -> Used for secure input reading to prevent buffer overflows
-   `strcspn()` (Internal) -> Used to sanitize the input by removing trailing newline characters.
-   `fflush(stdout)` -> Ensures the prompt is immediately visible on the terminal.
**Workflow Logic:**
1.  **READ:** Display `myShell>` and wait for user input.
2.  **VALIDATE:** Check if the input is `NULL` (Ctrl+D) or empty.
3.  **LOG:** Send the raw string to `add_to_history()`.
4.  **PARSE:** Call `parse_pipes()` to transform the string into a `Command` linked list.
5.  **DISPATCH:** * Check `execute_builtin()` first.
    -   If not a built-in, call `execute_pipeline()`.
6.  **CLEANUP:** Call `free_command_list()` to deallocate memory before the next prompt.

