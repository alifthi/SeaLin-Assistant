#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include "config.h"
#include "shell.h"

int run_subprocess(char* file_name, output_type* out){
    
    char cmd[50] = "bash ";
    strcat(cmd, file_name);
    int stdout_pipe[2], stderr_pipe[2];
    pipe(stdout_pipe);
    pipe(stderr_pipe);

    pid_t pid = fork();
    if (pid == 0) {
        dup2(stdout_pipe[1], STDOUT_FILENO);  
        dup2(stderr_pipe[1], STDERR_FILENO);  

        close(stdout_pipe[0]);
        close(stderr_pipe[0]);
        close(stdout_pipe[1]);
        close(stderr_pipe[1]);

        execl("/bin/sh", "sh", "-c", cmd, NULL);
        _exit(127);  
    }

    
    close(stdout_pipe[1]);
    close(stderr_pipe[1]);

    read_console(out->std_out, stdout_pipe[0]);
    read_console(out->std_err, stderr_pipe[0]);

    close(stdout_pipe[0]);
    close(stderr_pipe[0]);

    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        out->exit_code = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        out->exit_code = 128 + WTERMSIG(status);
    } else {
        out->exit_code = -1;
    }

    return 0;
}

int read_console(char **store_var, int fd){

    size_t size = 0;
    size_t capacity = MAX_OUT_CODE_LENGTH;
    char* buffer = malloc(capacity);
    if (!buffer) return NULL;

    ssize_t bytes;
    while ((bytes = read(fd, buffer + size, capacity - size - 1)) > 0) {
        size += bytes;
        if (size >= capacity - 1) {
            capacity *= 2;
            buffer = realloc(buffer, capacity);
            if (!buffer) return NULL;
        }
    }
    buffer[size] = '\0'; 
    *store_var = buffer;

    return 0;
}