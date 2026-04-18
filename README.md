# TEAMX Shell Project
## Alexandria University - Faculty of Computers and Data Science

### Team Members:
1. Mariam Khaled Ahmed 		        23011528
2. Mariam Hafez Saed		        23011150
3. Sondos Yasser Mohammed	        23010132
4. Soheir Mohammed Salah	        23010158
5. Mariam Farag Mohammed 	        23011531
6. Asmaa Abdallah Mosa 		        23011043
7. Salma Essam Ismail 		        23011286
8. Basmala Mahmoud El-Sayed 		23010140
9. Rania Ali Abo Zaid		        23010113
10. Shahd Waleed Bayoumy	        23010091

### How to run:
1. Open Terminal in this folder.
2. Type `make`.
3. Run using `./myShell`.

## Team Information
- **Team Number:** TEAMXX
- **Roles:** 

# Module: Error Handler Module for myShell:
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

# Module: Command Line Parser:
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

# Module: Built-in Commands of the shell:
- **Module Author:** shahd waleed bayoumy
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
