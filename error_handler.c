#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "error_handler.h"

void print_error(int error_code, const char *details){
	switch(error_code){
		case ERR_FORK_FAILED:
		fprintf(stderr, "myShell: fork failed: %s\n", strerror(errno));
		break;
		case ERR_EXEC_FAILED:
		fprintf(stderr, "myShell: excution failed: %s\n", strerror(errno));
		break;
		case ERR_PIPE_FAILED:
                fprintf(stderr, "myShell: pipe failed: %s\n", strerror(errno));
                break;
		case ERR_FILE_NOT_FOUND:
                fprintf(stderr, "myShell: %s: NO such file or directory\n", details);
                break;
		case ERR_PERMISSION_DENIED:
                fprintf(stderr, "myShell: %s: Permission denied\n", details);
                break;
		case ERR_DIR_NOT_FOUND:
                fprintf(stderr, "myShell: cd %s: No such directory\n", details);
                break;
		case ERR_CMD_NOT_FOUND:
                fprintf(stderr, "myShell: %s: command not found\n", details);
                break;
		case ERR_MEMORY:
                fprintf(stderr, "myShell: %s: memory allocation failed\n", details);
                break;
		default:
		fprintf(stderr, "myshell: unknown error\n");
}
}


int handle_fork_error(){
	print_error(ERR_FORK_FAILED, NULL);
	return ERR_FORK_FAILED;
}

int handle_exec_error(const char *command) {
	print_error(ERR_EXEC_FAILED, command);
	return ERR_EXEC_FAILED;
}

int handle_pipe_error() {
        print_error(ERR_PIPE_FAILED, NULL);
        return ERR_PIPE_FAILED;
}

int handle_file_error(const char *filename){
	if (errno == ENOENT){
		print_error(ERR_FILE_NOT_FOUND, filename);
		return ERR_FILE_NOT_FOUND;
	}else if (errno == EACCES) {
		print_error(ERR_PERMISSION_DENIED, filename);
		return ERR_PERMISSION_DENIED;
	}
	print_error(ERR_EXEC_FAILED, filename);
	return ERR_EXEC_FAILED;
}

int handle_cd_error(const char *path){
	if (errno == ENOENT) {
	print_error(ERR_DIR_NOT_FOUND, path);
	return ERR_DIR_NOT_FOUND;
	} else if (errno == EACCES) {
	print_error(ERR_PERMISSION_DENIED, path);
	return ERR_PERMISSION_DENIED;
}
	fprintf(stderr, "myShell: cd %s: Error changing directory\n", path);
	return ERR_EXEC_FAILED;
}

int handle_command_not_found(const char *command) {
	print_error(ERR_CMD_NOT_FOUND, command);
	return ERR_CMD_NOT_FOUND;
}
