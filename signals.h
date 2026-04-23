#ifndef SIGNALS_H
#define SIGNALS_H
#include <signal.h>

void setup_signals();
void handle_sigint(int sig);
#endif
