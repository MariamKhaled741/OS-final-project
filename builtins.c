#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "builtins.h"

#define MAX_HISTORY 100
char history_list[MAX_HISTORY][1024];
int history_count = 0;


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


void add_to_history(char *input) {
    if (history_count < MAX_HISTORY) {
        strncpy(history_list[history_count], input, 1024);
        history_count++;
    } else {
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            strcpy(history_list[i], history_list[i + 1]);
        }
        strncpy(history_list[MAX_HISTORY - 1], input, 1024);
    }
}


void show_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d  %s\n", i + 1, history_list[i]);
    }
}


int execute_builtin(char **args) {
    if (args[0] == NULL) return 0; 

    if (strcmp(args[0], "cd") == 0) { 
        shell_cd(args); 
        return 1; 
    }
    if (strcmp(args[0], "pwd") == 0) { 
        shell_pwd(); 
        return 1; 
    }
    if (strcmp(args[0], "exit") == 0) { 
        shell_exit(); 
        return 1; 
    }

    if (strcmp(args[0], "history") == 0) {
        show_history();
        return 1;
    }

    return 0; 
}
