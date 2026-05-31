#include <unistd.h>
#include "daemon_core.h"
#include "logger.h"
#include "config.h"
#include "pidfile.h"

int main() {
    make_daemon();

    if (check_and_create_pid_file("/tmp/daemon_app.pid") < 0) {
        return 1;
    }

    setup_signal_handling();
    load_config("/tmp/daemon.conf");
    init_logger("/tmp/daemon.log");

    log_message("Daemon started.");

    while (running) {
        if (reload_requested) {
            load_config("/tmp/daemon.conf");
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