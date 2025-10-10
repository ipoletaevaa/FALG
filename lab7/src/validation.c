#include "validation.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_valid_number_string(const char* str) {
    if (!str || *str == '\0') {
        return 0;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (!((c >= '0' && c <= '9') || 
              (c >= 'A' && c <= 'Z') || 
              (c >= 'a' && c <= 'z'))) {
            return 0;
        }
    }
    
    return 1;
}

char* remove_leading_zeros(const char* number_str) {
    if (!number_str) {
        return NULL;
    }
    
    size_t len = strlen(number_str);
    if (len == 0) {
        char* result = malloc(1);
        if (result) {
            result[0] = '\0';
        }
        return result;
    }
    
    size_t start_index = 0;
    while (start_index < len - 1 && number_str[start_index] == '0') {
        start_index++;
    }
    
    size_t result_len = len - start_index;
    char* result = malloc(result_len + 1);
    if (!result) {
        return NULL;
    }
    
    memcpy(result, number_str + start_index, result_len);
    result[result_len] = '\0';
    
    return result;
}

int is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

ValidationStatus validate_command_line_args(int argc, char** argv) {
    if (argc != 3) {
        return VALIDATION_INVALID_INPUT;
    }
    
    if (!argv[1] || !argv[2]) {
        return VALIDATION_INVALID_INPUT;
    }
    
    return VALIDATION_SUCCESS;
}

ValidationStatus validate_filenames_different(const char* filename1, const char* filename2) {
    if (!filename1 || !filename2) {
        return VALIDATION_INVALID_INPUT;
    }
    
    if (strcmp(filename1, filename2) == 0) {
        return VALIDATION_SAME_FILES;
    }
    
    return VALIDATION_SUCCESS;
}