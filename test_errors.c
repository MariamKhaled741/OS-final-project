#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "error_handler.h"

int main(){
	printf("Testing Error Handler Module \n");
	printf("============================\n\n");

	printf("Test 1: command not found\n");
	handle_command_not_found("xyzabc");
	printf("\n");

	printf("Test 2: fork error function\n");
        handle_fork_error();
        printf("\n");

	printf("Test 3: File not found\n");
        errno = ENOENT;
	handle_file_error("nonexistent.txt");
        printf("\n");

	printf("Test 4: Directorty not found\n");
        errno = ENOENT;
        handle_file_error("nonexistent.txt");
        printf("\n");

	printf("Test 5: pipe error\n"); 
        handle_pipe_error();
        printf("\n");

return 0;
}
