#ifndef NODES_H
#define NODES_H

#include "states.h"
#include "inference.h"
char* decide_next_node(state_type state);
char* split(const char* main_string, const char* needle, short index);
int inference_node(state_type *state, llama_inference *inference);
int search_node(state_type *state);
int shell_node(state_type *state);
int prepare_cmd(state_type* state);
int prepare_search_query(state_type* state);

#endif