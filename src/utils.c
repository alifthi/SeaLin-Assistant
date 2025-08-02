#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "utils.h"

char* get_user_prompt(char* input_string){
    char *line = NULL;
    size_t len = 0;
    printf("->");
    if (getline(&line, &len, stdin) == -1) {
        free(line);
        return NULL;
    }

    return line;
}
