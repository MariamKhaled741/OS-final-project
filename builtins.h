#ifndef BUILTINS_H
#define BUILTINS_H

int execute_builtin(char **args);
void shell_cd(char **args);
void shell_pwd();
void shell_exit();


void add_to_history(char *input); 

#endif
