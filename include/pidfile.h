#ifndef PIDFILE_H
#define PIDFILE_H

// Checks if the daemon is already running and creates a PID file.
int check_and_create_pid_file(const char* pid_file_path);

// Removes the PID file upon daemon termination.
void remove_pid_file(const char* pid_file_path);

#endif