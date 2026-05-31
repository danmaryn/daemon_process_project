#include "pidfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// Checks if the daemon is already running and creates a PID file.
int check_and_create_pid_file(const char* pid_file_path) {
    int fd = open(pid_file_path, O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        return -1;
    }

    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;

    if (fcntl(fd, F_SETLK, &fl) == -1) {
        close(fd);
        return -1;
    }

    if (ftruncate(fd, 0) == -1) {
        close(fd);
        return -1;
    }

    char pid_str[16];
    snprintf(pid_str, sizeof(pid_str), "%d\n", getpid());
    if (write(fd, pid_str, strlen(pid_str)) == -1) {
        close(fd);
        return -1;
    }

    return 0;
}

// Removes the PID file upon daemon termination.
void remove_pid_file(const char* pid_file_path) {
    unlink(pid_file_path);
}