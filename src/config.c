#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int daemon_sleep_interval = 1;

// Parses the configuration file to set daemon parameters.
void load_config(const char* file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "interval=", 9) == 0) {
            int val = atoi(line + 9);
            if (val > 0) {
                daemon_sleep_interval = val;
            }
        }
    }
    fclose(file);
}