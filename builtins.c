#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "builtins.h"

void shell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "myShell: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("myShell");
        }
    }
}

void shell_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd() error");
    }
}

void shell_exit() {
    exit(0);
}

int execute_builtin(char **args) {
    if (args[0] == NULL) return 1;
    if (strcmp(args[0], "cd") == 0) { shell_cd(args); return 1; }
    if (strcmp(args[0], "pwd") == 0) { shell_pwd(); return 1; }
    if (strcmp(args[0], "exit") == 0) { shell_exit(); return 1; }
    return 0;
}
