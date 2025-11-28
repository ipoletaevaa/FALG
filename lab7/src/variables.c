#include "variables.h"
#include <string.h>
#include <stdio.h>

variables_status_t variables_init(variables_t *vars) {
    if (vars == NULL) {
        return VARIABLES_NULL_POINTER;
    }
    
    for (int i = 0; i < VARIABLES_COUNT; i++) {
        vars->values[i] = 0;
        vars->initialized[i] = 0;
    }
    
    return VARIABLES_SUCCESS;
}

variables_status_t variables_set(variables_t *vars, char name, int value) {
    if (vars == NULL) {
        return VARIABLES_NULL_POINTER;
    }
    
    if (!variables_validate_name(name)) {
        return VARIABLES_INVALID_NAME;
    }
    
    int index = name - 'A';
    vars->values[index] = value;
    vars->initialized[index] = 1;
    
    return VARIABLES_SUCCESS;
}

variables_status_t variables_get(const variables_t *vars, char name, int *value) {
    if (vars == NULL || value == NULL) {
        return VARIABLES_NULL_POINTER;
    }
    
    if (!variables_validate_name(name)) {
        return VARIABLES_INVALID_NAME;
    }
    
    int index = name - 'A';
    if (!vars->initialized[index]) {
        return VARIABLES_INVALID_INDEX;
    }
    
    *value = vars->values[index];
    return VARIABLES_SUCCESS;
}

variables_status_t variables_is_initialized(const variables_t *vars, char name, int *initialized) {
    if (vars == NULL || initialized == NULL) {
        return VARIABLES_NULL_POINTER;
    }
    
    if (!variables_validate_name(name)) {
        return VARIABLES_INVALID_NAME;
    }
    
    int index = name - 'A';
    *initialized = vars->initialized[index];
    return VARIABLES_SUCCESS;
}

variables_status_t variables_reset(variables_t *vars, char name) {
    if (vars == NULL) {
        return VARIABLES_NULL_POINTER;
    }
    
    if (!variables_validate_name(name)) {
        return VARIABLES_INVALID_NAME;
    }
    
    int index = name - 'A';
    vars->initialized[index] = 0;
    return VARIABLES_SUCCESS;
}

variables_status_t variables_get_all_initialized(const variables_t *vars, char *buffer, size_t buffer_size) {
    if (vars == NULL || buffer == NULL) {
        return VARIABLES_NULL_POINTER;
    }
    
    size_t pos = 0;
    int first = 1;
    
    for (int i = 0; i < VARIABLES_COUNT; i++) {
        if (vars->initialized[i]) {
            char var_name = 'A' + i;
            int value = vars->values[i];
            
            int needed = snprintf(NULL, 0, "%s%c=%d", first ? "" : ", ", var_name, value);
            if (pos + needed + 1 >= buffer_size) {
                break;
            }
            
            pos += sprintf(buffer + pos, "%s%c=%d", first ? "" : ", ", var_name, value);
            first = 0;
        }
    }
    
    if (pos == 0) {
        buffer[0] = '\0';
    }
    
    return VARIABLES_SUCCESS;
}

int variables_validate_name(char name) {
    return (name >= 'A' && name <= 'Z');
}