#Error Handler Module for myShell

## Team Information
- **Team Number:** TEAMXX
- **Module Author:** Maryam Hafez
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




