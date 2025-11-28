#ifndef VARIABLES_H
#define VARIABLES_H

#include <stddef.h>

#define VARIABLES_COUNT 26
#define INVALID_VARIABLE_VALUE -1

typedef enum {
    VARIABLES_SUCCESS = 0,
    VARIABLES_INVALID_INDEX,
    VARIABLES_INVALID_NAME,
    VARIABLES_NULL_POINTER
} variables_status_t;

typedef struct {
    int values[VARIABLES_COUNT];
    int initialized[VARIABLES_COUNT];
} variables_t;

variables_status_t variables_init(variables_t *vars);
variables_status_t variables_set(variables_t *vars, char name, int value);
variables_status_t variables_get(const variables_t *vars, char name, int *value);
variables_status_t variables_is_initialized(const variables_t *vars, char name, int *initialized);
variables_status_t variables_reset(variables_t *vars, char name);
variables_status_t variables_get_all_initialized(const variables_t *vars, char *buffer, size_t buffer_size);
int variables_validate_name(char name);

#endif