#include "nodes.h"
#include "inference.h"

/*
    * Choosing next node
    * @param state: Graph state
    * @return: An string that tells what the next node is
*/
char* decide_next_node(state_type state){
    char* splited = split(state.messages, "<|im_start|>assistant");
    if(splited){
        return "continue";
    }
    return splited;
}

/*
    * Invoke model.
    * @param state: Graph state.
    * @param inference: llama_inference pointer.
    * @param assistant_response: To store the assistant response.
    * @return: An int that shows inference was successful.
*/
int inference_node(state_type *state, llama_inference *inference){
    int res = allocate_prompt(&inference, &state);
        if(res)
            return 1;
    res = run_inference(&inference, &state->assistant_response);
    if(res)
        return 1;
    return 0;
}

/*
    * Finds the last occurrence of needle in haystack.
    * @param haystack: The main string.
    * @param needle.
    * @return: The last occurrence of needle.
*/
char* split(const char* haystack, const char* needle) {
    char *result;
    char *p = strstr(haystack, needle);
    while (p) {
        result = p;
        p = strstr(p + 1, needle);
    }
    return result;
}