#include "logger.h"
#include <stdio.h>
#include <time.h>

static FILE *log_file = NULL;

static void get_time_string(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

void init_logger(const char* file_path) {
    log_file = fopen(file_path, "a");
}

void log_message(const char* message) {
    if (!log_file) return;
    char time_buffer[26];
    get_time_string(time_buffer, sizeof(time_buffer));
    fprintf(log_file, "[%s] %s\n", time_buffer, message);
    fflush(log_file);
}

void close_logger() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}