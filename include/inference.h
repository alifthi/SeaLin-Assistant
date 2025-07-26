#ifndef INFERENCE_H
#define INFERENCE_H

#include "config.h"
#include "states.h"
#include <string.h> 

// Forwarding types
typedef struct llama_model llama_model_forwarded;
typedef struct llama_vocab llama_vocab_forwarded;
typedef struct llama_context llama_context_fowarded;
typedef struct llama_tokens llama_tokens_forwarded;

// llama_inference type contains any variable related to llamacpp
typedef struct 
{
    llama_model_forwarded* model;
    llama_context_fowarded* ctx;
    llama_vocab_forwarded* vocab;
    int n_prompt;
}llama_inference;

// To load llama cpp backend
void load_backend();

// To load model
int load_model(char *path, llama_inference* inference);

// To get vocab
int get_vocab(llama_inference* inference);

// To get number of tokens in a prompt
int get_num_tokens(llama_inference* inference, state_type* state);

// Allocate a memory to prompt
int allocate_prompt(llama_inference* inference, state_type* state);

// Create a llama context
int create_ctx(llama_inference* inference);

#endif