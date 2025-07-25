#include "states.h"
#include "config.h"
#include <stdio.h>
#include <string.h>


/*
    * Initializes astate structure with default values
    * @param state: Input state
    * @return: Initialized state
*/
state_type init_default_state(state_type state){
    state.messages = NULL;
    state.search_query = NULL;
    state.shell_command = NULL;
    state.stderr = NULL;
    state.stdout = NULL;
    state.exit_code = NULL;

    state.messages = extend_messages(state.messages, SYSTEM_PROMPT); 
    
    return state;
}

/*
    * Extending a string to the main string.
    * @param Main_string: The main string
    * @param Addition: The string we want to add to main_string
    * @return: New allocated string with combined content
*/
char* extend_messages(char* main_string, const char* addition){
    if(!addition)
        return main_string;
    
    size_t current_len = main_string ? strlen(main_string) : 0;
    size_t addition_len = strlen(addition);
    size_t final_len = current_len + addition_len +1;
    if(final_len > MAX_MESSAGE_LENGTH - 128) {
        printf("[WARNING]  Message length is near to exceeds maximum allowed size\n");
    }
    char* new_string = realloc(main_string, final_len);
    if(!new_string){
        fprintf(stderr, "[Error] Failed to allocate memory for message extension\n");
        return main_string;
    }
    if(current_len == 0)
        strcpy(new_string, addition);
    else
        strcat(new_string, addition);
    return new_string;
}

/*
    * Safely frees a pointer and sets it to NULL
    @param ptr: Pointer 
*/
void free_ptr(char* ptr){
    if(ptr){
        free(ptr);
        ptr = NULL;
    }
}