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

#Error Handler Module for myShell
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

##error codes
- 0: success
- 1: fork failed
- 2: exec failed
- 3: pipe failed
- 4: file not found
- 5: permission denied
- 6: directory not found
- 127: command not found

## usage Examples
```c
#include "error_handler.h"

pid_t pid = fork();
if (pid < 0){
	handle_fork_error();
}
` ``` `
# Module: Command Line Parser
**Author:** Mariam Khaled  
**Student ID:** 23011528  
**Course:** Operating Systems - Spring 2026

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

## 4. Technical Implementation
The core of the module relies on a custom `struct`:

```c
struct Command {
    char **args;         
    char *input_file;     
    char *output_file;    
    int background;       
    struct Command *next; 
};
## 4. Technical Implementation
The main loop utilizes the parser by converting user input into a command list, passing it to the execution module, and ensuring memory is cleared afterward:

```c
// Example of how the main loop utilizes the parser
struct Command *cmd_list = parse_pipes(user_input);

if (cmd_list && cmd_list->args[0]) {
    /* * The cmd_list is passed to the Execution Module.
     * Example: execute_pipeline(cmd_list); 
     */
}

// Memory cleanup after execution to prevent leaks
free_command_list(cmd_list);

## 4. Technical Implementation
The main loop utilizes the parser by converting user input into a command list, passing it to the execution module, and ensuring memory is cleared afterward:

```c

struct Command *cmd_list = parse_pipes(user_input);

if (cmd_list && cmd_list->args[0]) {
    /* * The cmd_list is passed to the Execution Module.
     * Example: execute_pipeline(cmd_list); 
     */
}


free_command_list(cmd_list);
5. Development Roadmap
[x] Tokenization: Successful splitting of strings into individual tokens.

[x] Data Structure: Full implementation of the Linked List to support Pipes.

[x] Robustness: Seamless integration with error_handler.h for memory allocation failures.

[ ] Next Step: Implement logic to bypass fork() for built-in commands (cd, pwd, etc.).

[ ] Next Step: Final synchronization and stress-testing with the Execution engine.



>>>>>>> origin/master
