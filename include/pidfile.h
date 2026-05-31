#ifndef PIDFILE_H
#define PIDFILE_H

int check_and_create_pid_file(const char* pid_file_path);
void remove_pid_file(const char* pid_file_path);

#endif