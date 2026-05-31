#include "logger.h"
#include <stdio.h>
#include <time.h>
#include <syslog.h>

static FILE *log_file = NULL;

// Generates a formatted timestamp string.
static void get_time_string(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Internal function to format and write the message to the log file and syslog.
static void log_message(const char* level_str, int syslog_level, const char* message) {
    if (log_file) {
        char time_buffer[26];
        get_time_string(time_buffer, sizeof(time_buffer));
        fprintf(log_file, "[%s] [%s] %s\n", time_buffer, level_str, message);
        fflush(log_file);
    }
    syslog(syslog_level, "[%s] %s", level_str, message);
}

// Initializes the custom log file and system logger.
void init_logger(const char* file_path) {
    log_file = fopen(file_path, "a");
    openlog("daemon_app", LOG_PID | LOG_CONS, LOG_DAEMON);
}

// Logs an informational message.
void log_info(const char* message) {
    log_message("INFO", LOG_INFO, message);
}

// Logs an error message.
void log_error(const char* message) {
    log_message("ERROR", LOG_ERR, message);
}

// Closes the log file and disconnects from the system logger.
void close_logger() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
    closelog();
}