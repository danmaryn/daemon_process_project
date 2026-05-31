#include <unistd.h>
#include "daemon_core.h"
#include "logger.h"

int main() {
    make_daemon();
    setup_signal_handling();

    init_logger("/tmp/daemon.log");

    while (running) {
        log_message("Process is running...");
        sleep(1);
    }

    log_message("Process terminated gracefully.");
    close_logger();
    
    return 0;
}