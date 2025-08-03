#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h> 

typedef struct {
    int exit_code;
    char* std_out;
    char* std_err;
} output_type;

int run_subprocess(output_type* out);