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

// To load llama cpp backend
void load_backend();

// To load model
llama_model_forwarded* load_model(state_type state);

// To get vocab
llama_vocab_forwarded* get_vocab(llama_model_forwarded model);

// To get number of tokens in a prompt
int get_num_tokens(llama_vocab_forwarded vocab,char *prompt);

// Allocate a memory to prompt
llama_tokens_forwarded allocate_prompt(int n_prompt, llama_tokens_forwarded prompt_tokens, char *prompt,llama_vocab_forwarded vocab);

// Create a llama context
llama_context_fowarded* create_ctx();

#endif