#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

char** find_all_occurences(const char* str, const char* substr, int case_sensitive){
    if (str == NULL || substr == NULL){
        return NULL;
    }

    if (strlen(substr) == 0){
        char** result = malloc(1 * sizeof(char*));

    }

    int count = 0;
    const char* current_pos = str;


}