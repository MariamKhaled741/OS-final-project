#include "execution.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include "error_handler.h"


pid_t fg_pid = 0;

void execute_pipeline(struct Command *cmd_list) {
    if (!cmd_list) return;


    if (cmd_list->next == NULL && execute_builtin(cmd_list->args)) {
        return;
    }

    int pipe_fds[2];
    int input_fd = 0; 
    struct Command *current = cmd_list;

   
    while (current != NULL) {


        if (current->next != NULL) {
            if (pipe(pipe_fds) == -1) {
                handle_pipe_error(); 
                return;
            }
        }

        pid_t pid = fork();

        if (pid == 0) {                     
            

            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);


            if (input_fd != 0) {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }

            if (current->next != NULL) {
                close(pipe_fds[0]); 
                dup2(pipe_fds[1], STDOUT_FILENO);
                close(pipe_fds[1]);
            }

            if (current->input_file != NULL) {
                int fd_in = open(current->input_file, O_RDONLY);
                if (fd_in == -1) {
                    handle_file_error(current->input_file); 
                    _exit(EXIT_FAILURE);
                }
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }


            if (current->output_file != NULL) {
                int fd_out = open(current->output_file,
                                  O_WRONLY | O_CREAT | O_TRUNC,
                                  0644);
                if (fd_out == -1) {
                    handle_file_error(current->output_file); 
                    _exit(EXIT_FAILURE);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }


            execvp(current->args[0], current->args);
            handle_exec_error(current->args[0]); 
            _exit(EXIT_FAILURE);

        } else if (pid > 0) {                 
            

            if (input_fd != 0) close(input_fd);


            if (current->next != NULL) {
                close(pipe_fds[1]); 
                input_fd = pipe_fds[0]; 
            }


            if (current->background) {

                printf("[Background Process started with PID: %d]\n", pid);

            } else {
                fg_pid = pid; 
                waitpid(pid, NULL, 0); 
                fg_pid = 0;
            }

        } else {
            handle_fork_error(); 
        }

        current = current->next; 
    }
}
