#ifndef LOGGER_H
#define LOGGER_H

// Initializes the custom log file and system logger.
void init_logger(const char* file_path);

// Logs an informational message.
void log_info(const char* message);

// Logs an error message.
void log_error(const char* message);

// Closes the log file and disconnects from the system logger.
void close_logger();

#endif