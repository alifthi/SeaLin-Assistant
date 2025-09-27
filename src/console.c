#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "console.h"

char* get_user_prompt(char* input_string){
    char *line = NULL;
    size_t len = 0;
    printf("\033[1;34m->\033[0m ");
    if (getline(&line, &len, stdin) == -1) {
        free(line);
        return NULL;
    }

    return line;
}
