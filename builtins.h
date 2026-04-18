#ifndef BUILTINS_H
#define BUILTINS_H

void shell_cd(char **args);
void shell_pwd();
void shell_exit();
int execute_builtin(char **args);

#endif
