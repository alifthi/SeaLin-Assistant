#include "nodes.h"
#include "inference.h"
/*
    * Choosing next node
    * @param state: Graph state
    * @return: An string that tells what the next node is
*/
char* decide_next_node(state_type state){
    char* splited = split(state.assistant_response, "</think>",-1);
    if(strstr(splited, "shell_command") != NULL)
        return "shell_node";
    else if(strstr(splited, "search_request") != NULL)
        return "search_node";
    else
        return "nothing";
    }

/*
    * Invoke model.
    * @param state: Graph state.
    * @param inference: llama_inference pointer.
    * @param assistant_response: To store the assistant response.
    * @return: An int that shows inference was successful.
*/
int inference_node(state_type *state, llama_inference *inference){
    int res = allocate_prompt(inference, state);
    if(res)
        return 1;
    res = run_inference(inference, state);
    if(res)
        return 1;
    return 0;
}

/*
    * Preparing command and store in state->shell_command.
    * @param state: Graph state.
    * @return: returns 0 if it was successful.
*/
int prepare_cmd(state_type *state){
    char* splited = split(state->assistant_response, "</think>",-1);

    char* temp = split(splited, "```bash",-1);
    splited = temp;
    temp = split(splited, "```", 0);
    splited = temp;
    state->shell_command = splited;
    free(splited);
    return 0;
}


/*
    * Split haystack by needle and return section at index.
    * @param haystack: The main string.
    * @param needle: The delimiter.
    * @param index: Section index to return (-1 for last).
    * @return: The section at specified index.
*/
char* split(const char* haystack, const char* needle, short index) {
    const char *start = haystack;
    const char *start_tmp = haystack;
    const char *p;
    size_t dlen = strlen(needle);
    int i = 0;

    while (1) {
        p = strstr(start_tmp, needle);
        if(index==-1 && !p || i==index)
            break;
        if (!p) {
            return NULL;
        }
        start = start_tmp;
        start_tmp = p + dlen; 
        i++;
    }

    p = strstr(start, needle);
    size_t len = p ? (size_t)(p - start) : strlen(start);

    char *token = malloc(len + 1);
    if (!token) return NULL;
    memcpy(token, start_tmp, len);
    token[len] = '\0';
    return token;
}