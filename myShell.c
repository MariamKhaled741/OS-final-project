#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_handler.h"

#define MAX_ARGS 64
#define MAX_LINE 1024

struct Command {
    char **args;
    char *input_file;
    char *output_file;
    int background;
    struct Command *next;
};

void free_command_list(struct Command *head) {
    while (head != NULL) {
        struct Command *temp = head;
        head = head->next;
        free(temp->args);
        free(temp);
    }
}

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

    while (token != NULL) {
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

//pipes
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

int main() {
    char line[MAX_LINE];

while (1) {
        printf("myShell> ");
        if (!fgets(line, MAX_LINE, stdin)) break;

        line[strcspn(line, "\n")] = 0;
        if (strcmp(line, "exit") == 0) break;
        if (strlen(line) == 0) continue;

        struct Command *cmd_list = parse_pipes(line);
        
        struct Command *curr = cmd_list;
        int p_idx = 0;
        while (curr != NULL) {
            printf("--- Command [%d] ---\n", p_idx++);
            printf("Exec: %s\n", curr->args[0] ? curr->args[0] : "NONE");
            if (curr->input_file) printf("In: %s\n", curr->input_file);
            if (curr->output_file) printf("Out: %s\n", curr->output_file);
            curr = curr->next;
        }
        printf("------------------\n");
        free_command_list(cmd_list);
    }

    return 0;
}
