#include "config.h"

struct state
{
    char messages[MAX_MESSAGE_LENGTH];
    char search_query[MAX_SEARCH_QUERY_LENGTH];
    char stdout[MAX_STDOUT_LENGTH];
    char stderr[MAX_STDERR_LENGTH];
    int exit_code;
};