#ifndef NODES_H
#define NODES_H

#include "states.h"

char* decide_next_node(state_type state);
char* split(const char* main_string, const char* needle);
int inference_node(state_type state);
int search_node(state_type state);
int prepare_cmd(state_type* state);
int prepare_search_query(state_type* state);

#endif