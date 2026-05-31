#ifndef DAEMON_CORE_H
#define DAEMON_CORE_H

#include <signal.h>

extern volatile sig_atomic_t running;

void make_daemon();
void setup_signal_handling();

#endif