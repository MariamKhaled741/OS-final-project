#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_handler.h"
#include "execution.h"
#include "builtins.h"  

#define MAX_LINE 1024
#define MAX_ARGS 64


struct Command* parse_single_command(char *line) {
    struct Command *cmd = malloc(sizeof(struct Command));
    if (cmd == NULL) {
        print_error(ERR_MEMORY, "Command Allocation");
        return NULL;
    }

    cmd->args = malloc(MAX_ARGS * sizeof(char*));
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->background = 0;
    cmd->next = NULL;

    char *token = strtok(line, " \t\n");
    int i = 0;

    while (token != NULL && i < MAX_ARGS - 1) {
        if (strcmp(token, "&") == 0) {
            cmd->background = 1;
        } else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t\n");
            if (token) cmd->input_file = token;
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t\n");
            if (token) cmd->output_file = token;
        } else {
            cmd->args[i++] = token;
        }
        token = strtok(NULL, " \t\n");
    }
    cmd->args[i] = NULL;
    return cmd;
}


struct Command* parse_pipes(char *line) {
    struct Command *head = NULL;
    struct Command *last = NULL;
    char *saveptr;
    
    char *sub_command = strtok_r(line, "|", &saveptr);
    while (sub_command != NULL) {
        struct Command *new_cmd = parse_single_command(sub_command);
        if (head == NULL) {
            head = new_cmd;
            last = head;
        } else {
            last->next = new_cmd;
            last = new_cmd;
        }
        sub_command = strtok_r(NULL, "|", &saveptr);
    }
    return head;
}


void free_command_list(struct Command *head) {
    while (head != NULL) {
        struct Command *temp = head;
        head = head->next;
        if (temp->args) free(temp->args);
        free(temp);
    }
}


int main() {
    char line[MAX_LINE];


    printf("Welcome to myShell!\n");

    while (1) {

        printf("myShell> "); 
        

        if (!fgets(line, MAX_LINE, stdin)) {
            printf("\nExiting myShell... Goodbye!\n");
            break;
        }


        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) {
            continue;
        }


        add_to_history(line); 
        

        struct Command *cmd_list = parse_pipes(line);
        

        if (cmd_list && cmd_list->args && cmd_list->args[0]) {

            if (!execute_builtin(cmd_list->args)) {
             
                execute_pipeline(cmd_list); 
            }
        }
        

        if (cmd_list) {
            free_command_list(cmd_list);
        }
    }

    return 0;
}
