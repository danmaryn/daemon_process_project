#ifndef DAEMON_CORE_H
#define DAEMON_CORE_H

#include <signal.h>

extern volatile sig_atomic_t running;
extern volatile sig_atomic_t reload_requested;

// Forks the process and sets it up as a background daemon.
void make_daemon();

// Registers the signal handlers for graceful shutdown and config reloading.
void setup_signal_handling();

#endif