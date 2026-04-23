#include "signals.h"
#include "execution.h" 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigint(int sig) {
    if (fg_pid != 0) {

        kill(fg_pid, SIGINT);
        printf("\n");
    } else {

        printf("\nmyShell> ");
        fflush(stdout);
    }
}

void setup_signals() {

    signal(SIGINT, handle_sigint);


    signal(SIGTSTP, SIG_IGN);
}
