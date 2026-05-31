#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

volatile sig_atomic_t running = 1;

void handle_signal(int sig) {
    running = 0;
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

void get_time_string(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

int main() {
    make_daemon();

    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    FILE *log_file = fopen("/tmp/daemon.log", "a");
    if (!log_file) return 1;

    char time_buffer[26];

    while (running) {
        get_time_string(time_buffer, sizeof(time_buffer));
        fprintf(log_file, "[%s] Process is running...\n", time_buffer);
        fflush(log_file);
        sleep(1);
    }

    get_time_string(time_buffer, sizeof(time_buffer));
    fprintf(log_file, "[%s] Process terminated gracefully.\n", time_buffer);
    fclose(log_file);
    
    return 0;
}