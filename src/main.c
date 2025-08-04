#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "states.h"
#include "inference.h"
#include "console.h"
#include "shell.h"

int main(){
    llama_inference inference;
    state_type state;
    char *user_prompt;

    memset(&inference, 0, sizeof(llama_inference));
    memset(&state, 0, sizeof(state_type));

    init_default_state(&state);
    load_backend();

    int res = load_model(DEFAULT_MODEL_PATH, &inference);
    
    if(res){
        free_llama_inference(&inference);
        return 1;
    }
    
    res = get_vocab(&inference);
    if(res){
        free_llama_inference(&inference);
        return 1;
    }

    res = create_ctx(&inference);
    if(res){
        free_llama_inference(&inference);
        return 1;
    }
    
    res = set_sampler(&inference);
    if(res){
        free_llama_inference(&inference);
        return 1;
    }

    while (1)
    {
        user_prompt = get_user_prompt(&user_prompt); 
        if(strcmp(user_prompt, "exit\n") == 0){
            break;
        }
        state.messages = extend_messages(state.messages, "<|im_start|>user\n");
        user_prompt = extend_messages(user_prompt, "<|im_end|>\n<|im_start|>assistant");
        state.messages = extend_messages(state.messages, user_prompt);
        res = allocate_prompt(&inference, &state);
        if(res){
            free_llama_inference(&inference);
            return 1;
        }
        
        res = run_inference(&inference);
        if(res){
            free_llama_inference(&inference);
            return 1;
        }
    }
     
    free(user_prompt);
    free_ptr(&state);
    free_llama_inference(&inference);
    return 0;
}