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
    @param path: The path of model.
    @param inference: inference object.
    @return: returns 0 if load was succeed
*/
int load_model(char *path, llama_inference *inference){
    struct llama_model_params model_params = llama_model_default_params();
    model_params.n_gpu_layers = N_GPU_LAYERS;

    inference->model = llama_model_load_from_file(path, model_params);
    if(inference->model == NULL){
        printf("[Error] Faild to load model %s", path);
        return 1;
    }
    return 0;
}

/*
    * Loading vocab
    @param inference: inference object.
    @return: returns 0 if load was succeed
*/
int get_vocab(llama_inference *inference){
    inference->vocab = llama_model_get_vocab(inference->model);
    if(inference->vocab == NULL){
        printf("[Error] Faild to load vocab");
        return 1;
    }
    return 0;
}