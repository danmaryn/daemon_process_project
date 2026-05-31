#include "daemon_core.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

volatile sig_atomic_t running = 1;
volatile sig_atomic_t reload_requested = 0;

// Handles incoming system signals to control the daemon state.
static void handle_signal(int sig) {
    if (sig == SIGHUP) {
        reload_requested = 1;
    } else {
        running = 0;
    }
}

// Registers the signal handlers for graceful shutdown and config reloading.
void setup_signal_handling() {
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);
    signal(SIGHUP, handle_signal);
}

// Forks the process and sets it up as a background daemon.
void make_daemon() {
    pid_t pid = fork();
    
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    if (setsid() < 0) exit(EXIT_FAILURE);

    umask(0);
    if (chdir("/") < 0) exit(EXIT_FAILURE);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}