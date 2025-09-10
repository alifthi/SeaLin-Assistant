#include "nodes.h"

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

char* split(const char* haystack, const char* needle) {
    char *result;
    char *p = strstr(haystack, needle);
    while (p) {
        result = p;
        p = strstr(p + 1, needle);
    }
    return result;
}