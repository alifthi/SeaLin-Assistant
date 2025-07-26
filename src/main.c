#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "states.h"
#include "inference.h"

int main(){
    llama_inference inference;
    state_type state;

    
    memset(&inference, 0, sizeof(llama_inference));
    memset(&state, 0, sizeof(state_type));

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

    free_llama_inference(&inference);
    return 0;
}