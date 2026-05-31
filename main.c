#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main() {
    FILE *log_file = fopen("daemon.log", "a");
    if (!log_file) {
        return 1;
    }

    while (1) {
        time_t now = time(NULL);
        fprintf(log_file, "Process is running timestamp: %ld\n", now);
        fflush(log_file);
        sleep(1);
    }

    fclose(log_file);
    return 0;
}