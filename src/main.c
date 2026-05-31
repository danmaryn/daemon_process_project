#include <unistd.h>
#include "daemon_core.h"
#include "logger.h"
#include "config.h"

int main() {
    make_daemon();
    setup_signal_handling();

    load_config("/tmp/daemon.conf");
    init_logger("/tmp/daemon.log");

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
    
    return 0;
}