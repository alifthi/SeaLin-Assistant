#include "llama_wraper.h"
#include "inference.h"
#include "states.h"
#include "config.h"
/*
    * loading ggml backend
*/
void load_backend(){
    ggml_backend_load_all();
}

/*
    * Loading model
    * @param path: The path of model.
    * @param inference: inference object.
    * @return: returns 0 if load was succeed
*/
int load_model(char *path, llama_inference *inference){
    struct llama_model_params model_params = llama_model_default_params();
    model_params.n_gpu_layers = N_GPU_LAYERS;

    inference->model = llama_model_load_from_file(path, model_params);
    if(inference->model == NULL){
        fprintf(stderr,"[Error] Faild to load model %s\n", path);
        return 1;
    }
    return 0;
}

/*
    * Loading vocab
    * @param inference: inference object.
    * @return: returns 0 if load was succeed
*/
int get_vocab(llama_inference *inference){
    inference->vocab = llama_model_get_vocab(inference->model);
    if(inference->vocab == NULL){
        fprintf(stderr,"[Error] Faild to load vocab\n");
        return 1;
    }
    return 0;
}

/*
    * allocate prompt_tokens
    * @param inference: inference object.
    * @param state: state object.
    * @return: returns 0 if tokenization was succeed.
*/
int allocate_prompt(llama_inference* inference, state_type* state){
    inference->n_prompt = -llama_tokenize(inference->vocab, state->messages, strlen(state->messages), NULL, 0, true, true);
    inference->prompt_tokens = (llama_token *)malloc(inference->n_prompt * sizeof(llama_token));
    if (llama_tokenize(inference->vocab, state->messages, strlen(state->messages), inference->prompt_tokens, inference->n_prompt, true, true) < 0) {
        fprintf(stderr, "[Error] Failed to tokenize the prompt\n");
        return 1;
    }
    return 0;
}

/*
    * Initialization of llama contex
    * @param inference: Inference object. 
*/
int create_ctx(llama_inference* inference){
    struct llama_context_params ctx_params = llama_context_default_params();
    ctx_params.n_ctx = inference->n_prompt + MAX_MESSAGE_LENGTH - 1;
    ctx_params.n_batch = inference->n_prompt;
    ctx_params.no_perf = false;

    inference->ctx = llama_init_from_model(inference->model, ctx_params);
    if (inference->ctx == NULL){
        fprintf(stderr, "[Error] Failed initialize contex\n");
        return 1;
    }
    return 0;
}

/*
    * Set sampler
    * @param inference: llama_inference object 
*/
int set_sampler(llama_inference* inference){
    struct llama_sampler_chain_params chain_params = llama_sampler_chain_default_params();
    chain_params.no_perf = false;

    inference->smplr = llama_sampler_chain_init(chain_params);
    llama_sampler_chain_add(inference->smplr, llama_sampler_init_greedy());
    return 0;
}

/*
    * Unallocates llama_inference object
    * @param inference: A llama_inference object
*/
int free_llama_inference(llama_inference* inference){
    
    if(!inference->model==NULL)
        llama_free_model(inference->model);

    if (!inference->smplr == NULL)
        llama_sampler_free(inference->smplr);

    if (!inference->ctx == NULL)
        llama_free(inference->ctx);

    if (!inference->prompt_tokens == NULL)
        free(inference->prompt_tokens);
    
    return 0;
}