#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("\nmyShell> ");
    fflush(stdout); 
}

void setup_signals() {
    signal(SIGINT, handle_sigint);
    signal(SIGTSTP, SIG_IGN);
}
