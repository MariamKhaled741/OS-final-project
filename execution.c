#include "execution.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>


pid_t fg_pid = 0;

void execute_pipeline(struct Command *cmd_list) {
    if (!cmd_list) return;

    /* ============================================= */
    /* EXECUTION (fork + exec) */
    /* ============================================= */

    /* Built-in commands (cd, pwd, exit, history) */
    if (cmd_list->next == NULL && execute_builtin(cmd_list->args)) {
        return;
    }

    /* === SINGLE COMMAND EXECUTION === */
    pid_t pid = fork();

    if (pid == 0) {                     /* CHILD PROCESS */
        /* ===================================================== */
/* REDIRECTION SECTION: Handle < and > operators */
/* ===================================================== */
// NOTE: This redirection is PIPE-safe (only modifies STDIN/STDOUT in child process)

/* -------------------- INPUT REDIRECTION (<) -------------------- */
if (cmd_list->input_file != NULL) {
    // If user provided an input file (e.g., cat < input.txt)

    int fd_in = open(cmd_list->input_file, O_RDONLY);
    // Open file in read-only mode

    if (fd_in == -1) {
        // Error opening file (file doesn't exist or permission denied)

        perror("Error: cannot open input file");
        _exit(EXIT_FAILURE);
        // Important: terminate child process immediately
    }

    if (dup2(fd_in, STDIN_FILENO) == -1) {
        // Replace standard input with file descriptor

        perror("Error: dup2 failed for input");
        close(fd_in);
        _exit(EXIT_FAILURE);
    }

    close(fd_in);
    // Close original descriptor after duplication
}


/* -------------------- OUTPUT REDIRECTION (>) -------------------- */
if (cmd_list->output_file != NULL) {
    // If user provided an output file (e.g., ls > output.txt)

    int fd_out = open(cmd_list->output_file,
                      O_WRONLY | O_CREAT | O_TRUNC,
                      0644);
    // O_WRONLY  -> write only
    // O_CREAT   -> create file if not exists
    // O_TRUNC   -> overwrite file if exists
    // 0644      -> permissions (rw-r--r--)

    if (fd_out == -1) {
        // Error creating/opening file

        perror("Error: cannot open output file");
        _exit(EXIT_FAILURE);
    }

    if (dup2(fd_out, STDOUT_FILENO) == -1) {
        // Replace standard output with file

        perror("Error: dup2 failed for output");
        close(fd_out);
        _exit(EXIT_FAILURE);
    }

    close(fd_out);
    // Close original descriptor
}


/* ===================================================== */
/* EXECUTE COMMAND */
/* ===================================================== */


execvp(cmd_list->args[0], cmd_list->args);

perror("Error: command execution failed");
_exit(EXIT_FAILURE);

}

    else if (pid > 0) {                 /* PARENT PROCESS */
        fg_pid = pid;   /* Signal handling teammate will use this */

        /* ============================================= */
        /* TODO: Background processes person (&) */
        /* Add your code here:
        if (cmd_list->background) {
            printf("[...] Background process started (PID %d)\n", pid);
            // do NOT call waitpid()
        } else {
            waitpid(pid, NULL, 0);
            fg_pid = 0;
        }
        */
        /* ============================================= */

        waitpid(pid, NULL, 0);   /* Default: wait for foreground (your part) */
        fg_pid = 0;
    }
    else {
        handle_fork_error();
    }

    /* ============================================= */
    /* TODO: Pipes person (|) */
    /* If you want to support multiple commands with |, 
       you must completely rewrite this function to use a loop,
       create multiple pipes, and fork multiple children.
       For now it only supports single commands. */
    /* ============================================= */

    /* ============================================= */
    /* TODO: Signal handling person (Ctrl+C) */
    /* You can add the SIGINT handler in myShell.c or here.
       fg_pid is already declared and set for you. */
    /* ============================================= */
}
