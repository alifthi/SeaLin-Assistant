#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> 
#include "config.h"
#include "shell.h"

int run_subprocess(char* file_name, output_type* out){
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "bash %s", file_name);
    
    int stdout_pipe[2], stderr_pipe[2];
    if (pipe(stdout_pipe) == -1 || pipe(stderr_pipe) == -1) {
        return -1;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        close(stdout_pipe[0]); close(stdout_pipe[1]);
        close(stderr_pipe[0]); close(stderr_pipe[1]);
        return -1;
    }
    
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

    if (read_console(&out->std_out, stdout_pipe[0]) != 0 ||
        read_console(&out->std_err, stderr_pipe[0]) != 0) {
        close(stdout_pipe[0]);
        close(stderr_pipe[0]);
        return -1;
    }

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
    if (!buffer) return -1;

    ssize_t bytes;
    while ((bytes = read(fd, buffer + size, capacity - size - 1)) > 0) {
        size += bytes;
        if (size >= capacity - 1) {
            capacity *= 2;
            char* new_buffer = realloc(buffer, capacity);
            if (!new_buffer) {
                free(buffer);
                return -1;
            }
            buffer = new_buffer;
        }
    }
    buffer[size] = '\0'; 
    *store_var = buffer;
    return 0;
}