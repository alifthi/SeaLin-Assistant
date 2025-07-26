#include "llama_wraper.h"
#include "inference.h"

void load_backend(){
    ggml_backend_load_all();
}