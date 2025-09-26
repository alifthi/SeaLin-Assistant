#include <stdio.h>
#include "states.h"
#include "inference.h"
#include "shell.h"
#include "nodes.h"


int run_graph(state_type *state, llama_inference *inference, output_type *cmd_out){

    int res = inference_node(state, inference);
    state->messages = extend_messages(state->messages, state->assistant_response);
    if(res)
        return 1;
    char* next_node = decide_next_node(*state);
    if(next_node == "shell_node"){
        prepare_cmd(state);
        res = shell_node(state, cmd_out);
        if(res)
            return 1;
    }
    return 0;
}