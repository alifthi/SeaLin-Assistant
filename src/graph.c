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
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "<|im_start|>system\nHere is the out put of the command:\nExit code: %i\nStd out: %s\nStd Error: %s\n<|im_end|>\n<|im_start|>Assistant\n",
                cmd_out->exit_code, cmd_out->std_out, cmd_out->std_err);
        state->messages = extend_messages(state->messages, buffer);
        run_graph(state, inference, cmd_out);
    }
    return 0;
}