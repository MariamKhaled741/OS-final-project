#ifndef EXECUTION_H

#define EXECUTION_H

#include "error_handler.h"

#include "builtins.h"

#include <sys/types.h>

struct Command {

    char **args;

    char *input_file;

    char *output_file;

    int background;

    struct Command *next;

};

extern pid_t fg_pid;

void execute_pipeline(struct Command *cmd_list);

#endif
