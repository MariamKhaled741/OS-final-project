<<<<<< HEAD
# TEAMX Shell Project
## Alexandria University - Faculty of Computers and Data Science

### Team Members:
<<<<<<< HEAD
1. Mariam Khaled Ahmed 		23011528
2. Mariam Hafez Saed		23011150
3. Sondos Yasser Mohammed	23010132
4. Soheir Mohammed Salah	23010158
5. Mariam Farag Mohammed 	23011531
6. Asmaa Abdallah Mosa 		23011043
7. Salma Essam Ismail 		23011286
8. Basmala Mahmoud 		23010140
9. Rania Ali Abo Zaid		23010113
10. Shahd Waleed Bayoumy	XXXXXXXX

=======
1. Mariam Khaled
2. Mariam Hafez Saed
3. Sondos Yasser Mohammed
4. Sohier Mohammed Salah
5. Mariam Farag Mohammed 
6. Asmaa Abdallah Mosa 
7. Salma Essam Ismail 
8. Basmala Mahmoud 
9. Rania Ali 
10. Shahd Waleed Bayoumy 
>>>>>>> 0c9cdac666efa793993d7ba07255cbf235e9c11d

### How to run:
1. Open Terminal in this folder.
2. Type `make`.
3. Run using `./myShell`.
=======
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




>>>>>>> origin/master
