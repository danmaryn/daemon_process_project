#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "daemon_core.h"
#include "logger.h"
#include "config.h"
#include "pidfile.h"

void print_help(const char* prog_name) {
    printf("Usage: %s [OPTIONS]\n", prog_name);
    printf("Options:\n");
    printf("  -c <file>   Specify configuration file path\n");
    printf("  -h          Show this help message\n");
}

int main(int argc, char *argv[]) {
    int opt;
    char config_path[256] = "/tmp/daemon.conf";

    while ((opt = getopt(argc, argv, "c:h")) != -1) {
        switch (opt) {
            case 'c':
                snprintf(config_path, sizeof(config_path), "%s", optarg);
                break;
            case 'h':
                print_help(argv[0]);
                return 0;
            default:
                print_help(argv[0]);
                return 1;
        }
    }

    make_daemon();

    if (check_and_create_pid_file("/tmp/daemon_app.pid") < 0) {
        return 1;
    }

    setup_signal_handling();
    load_config(config_path);
    init_logger("/tmp/daemon.log");

    log_message("Daemon started.");

    while (running) {
        if (reload_requested) {
            load_config(config_path);
            log_message("Configuration reloaded.");
            reload_requested = 0;
        }

        log_message("Process is running...");
        sleep(daemon_sleep_interval);
    }

    log_message("Process terminated gracefully.");
    close_logger();
    remove_pid_file("/tmp/daemon_app.pid");
    
    return 0;
}