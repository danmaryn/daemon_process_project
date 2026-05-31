#include "daemon_core.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

volatile sig_atomic_t running = 1;

static void handle_signal(int sig) {
    running = 0;
}

void setup_signal_handling() {
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);
}

void make_daemon() {
    pid_t pid = fork();
    
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    if (setsid() < 0) exit(EXIT_FAILURE);

    umask(0);
    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}