#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#define ERR_SUCCESS 0
#define ERR_FORK_FAILED 1
#define ERR_EXEC_FAILED 2
#define ERR_PIPE_FAILED 3
#define ERR_FILE_NOT_FOUND 4
#define ERR_PERMISSION_DENIED 5
#define ERR_DIR_NOT_FOUND 6
#define ERR_CMD_NOT_FOUND 127
#define ERR_MEMORY 8
#define ERR_INVALID_INPUT 9

void print_error(int error_code, const char *details);
int handle_fork_error();
int handle_exec_error(const char *command);
int handle_pipe_error();
int handle_file_error(const char *filename);
int handle_cd_error(const char *path);
int handle_command_not_found(const char *command);

#endif



