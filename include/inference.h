#ifndef INFERENCE_H
#define INFERENCE_H

#include "config.h"
#include "states.h"

typedef struct llama_model llama_model_forwarded;
typedef struct llama_vocab llama_vocab_forwarded;
typedef struct llama_context llama_context_fowarded;


void load_backend();

llama_model_forwarded* load_model(state_type state);

llama_vocab_forwarded* get_vocab(llama_model_forwarded model);

llama_context_fowarded* create_ctx();

#endif