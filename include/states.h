#ifndef STATES_H
#define STATES_H

#include "config.h"
typedef struct {
    char* messages;           // Message contains user, system, assistant and tool messages
    char assistant_response[4096]; // Stores assistant response
    char* search_query;       // Stores the search query
    char* shell_command;      // Stores the shell command to be executed
    char* stdout;             // Stores the standard output of the executed command
    char* stderr;             // Stores the standard error of the executed command
    int exit_code;            // Stores the exit code of the executed command
} state_type;

char* extend_messages(char* main_string, const char* addition);

void free_ptr(state_type* state);

int init_default_state(state_type* state);

#endif