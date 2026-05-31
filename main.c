#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

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

int main() {
    make_daemon();

    FILE *log_file = fopen("/tmp/daemon.log", "a");
    if (!log_file) return 1;

    while (1) {
        time_t now = time(NULL);
        fprintf(log_file, "Process is running timestamp: %ld\n", now);
        fflush(log_file);
        sleep(1);
    }

    fclose(log_file);
    return 0;
}