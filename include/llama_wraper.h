/**
 * @file llama_wrapper.h
 * @brief Wrapper for llama.cpp headers with local includes
 */

#ifndef LLAMA_WRAPPER_H
#define LLAMA_WRAPPER_H

#include "ggml.h"
#include "llama.h"

#define LLAMA_WRAPPER_VERSION "1.0.0"

static inline const char* llama_wrapper_version(void) {
    return LLAMA_WRAPPER_VERSION;
}

static inline bool llama_wrapper_model_load_safe(struct llama_model** model, 
                                                 const char* path, 
                                                 struct llama_model_params params) {
    *model = llama_model_load_from_file(path, params);
    return (*model != NULL);
}

#endif 