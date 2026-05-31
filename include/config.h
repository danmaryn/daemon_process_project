#ifndef CONFIG_H
#define CONFIG_H

extern int daemon_sleep_interval;

// Parses the configuration file to set daemon parameters.
void load_config(const char* file_path);

#endif