#include "execution.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include "error_handler.h"

/* Global variable for the foreground process ID */
pid_t fg_pid = 0;

void execute_pipeline(struct Command *cmd_list) {
    if (!cmd_list) return;

    /* Handle Built-in commands (cd, pwd, exit, etc.) */
    if (cmd_list->next == NULL && execute_builtin(cmd_list->args)) {
        return;
    }

    int pipe_fds[2];
    int input_fd = 0; // Holder for the read-end of the previous pipe stage
    struct Command *current = cmd_list;

    /* ===================================================== */
    /* MULTI-COMMAND EXECUTION LOOP (Pipes Implementation)   */
    /* ===================================================== */
    while (current != NULL) {

        /* Create a pipe if there is a next command in the chain */
        if (current->next != NULL) {
            if (pipe(pipe_fds) == -1) {
                handle_pipe_error(); // Integrated from error_handler.c
                return;
            }
        }

        pid_t pid = fork();

        if (pid == 0) {                     /* CHILD PROCESS */

            /* --- PIPE LOGIC: Redirecting STDIN/STDOUT for the pipeline --- */
            if (input_fd != 0) {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }

            if (current->next != NULL) {
                close(pipe_fds[0]); // Close unused read end
                dup2(pipe_fds[1], STDOUT_FILENO);
                close(pipe_fds[1]);
            }

            /* ===================================================== */
            /* REDIRECTION SECTION: Handle < and > operators         */
            /* ===================================================== */

            /* -------------------- INPUT REDIRECTION (<) -------------------- */
            if (current->input_file != NULL) {
                /* Open the input file in read-only mode (O_RDONLY) */
                int fd_in = open(current->input_file, O_RDONLY);

                if (fd_in == -1) {
                    /* Handle errors like 'File not found' or 'Permission denied' */
                    handle_file_error(current->input_file); 
                    _exit(EXIT_FAILURE);
                }

                /* Replace standard input with the file descriptor */
                if (dup2(fd_in, STDIN_FILENO) == -1) {
                    perror("Error: dup2 failed for input");
                    close(fd_in);
                    _exit(EXIT_FAILURE);
                }
                close(fd_in);
            }

            /* -------------------- OUTPUT REDIRECTION (>) -------------------- */
            if (current->output_file != NULL) {
                /* * O_WRONLY -> write only
                 * O_CREAT  -> create file if it does not exist
                 * O_TRUNC  -> overwrite file if it already exists
                 * 0644     -> permissions: owner(rw-), group(r--), others(r--)
                 */
                int fd_out = open(current->output_file,
                                  O_WRONLY | O_CREAT | O_TRUNC,
                                  0644);

                if (fd_out == -1) {
                    handle_file_error(current->output_file); 
                    _exit(EXIT_FAILURE);
                }

                /* Replace standard output with the file descriptor */
                if (dup2(fd_out, STDOUT_FILENO) == -1) {
                    perror("Error: dup2 failed for output");
                    close(fd_out);
                    _exit(EXIT_FAILURE);
                }
                close(fd_out);
            }

            /* ===================================================== */
            /* EXECUTE COMMAND                                       */
            /* ===================================================== */
            execvp(current->args[0], current->args);
            
            /* If execvp fails, report the error using the integrated handler */
            handle_exec_error(current->args[0]); 
            _exit(EXIT_FAILURE);

        } else if (pid > 0) {                 /* PARENT PROCESS */
            
            fg_pid = pid; // Store PID for signal handling (e.g., Ctrl+C)

            /* Clean up the input descriptor from the previous pipe stage */
            if (input_fd != 0) close(input_fd);

            /* Prepare the current pipe's read-end for the next command */
            if (current->next != NULL) {
                close(pipe_fds[1]); // Close write end in parent
                input_fd = pipe_fds[0]; // Next command will read from this end
            }

            /* * TODO: The Process Management teammate will add background 
             * execution logic (&) and job control here.
             * Currently, the shell waits for each command by default.
             */
            waitpid(pid, NULL, 0); 
            fg_pid = 0;

        } else {
            /* Forking failed (e.g., system out of resources) */
            handle_fork_error(); 
        }

        current = current->next; // Move to next command in the pipeline
    }
}
