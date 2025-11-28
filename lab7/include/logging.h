#ifndef LOGGING_H
#define LOGGING_H

#include "variables.h"
#include "parser.h"

typedef enum {
    LOGGING_SUCCESS = 0,
    LOGGING_FILE_ERROR,
    LOGGING_NULL_POINTER
} logging_status_t;

logging_status_t logging_init(const char *filename);
logging_status_t logging_close(void);
logging_status_t logging_write_entry(int line_number, const char *original_line, const variables_t *vars, operation_type_t op_type);

#endif