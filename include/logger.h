#ifndef LOGGER_H
#define LOGGER_H

void init_logger(const char* file_path);
void log_message(const char* message);
void close_logger();

#endif