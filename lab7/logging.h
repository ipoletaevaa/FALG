#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "variables.h"
#include "parser.h"
#include "logging.h"

typedef enum {
    INTERPRETER_SUCCESS = 0,
    INTERPRETER_FILE_ERROR,
    INTERPRETER_SYNTAX_ERROR,
    INTERPRETER_MEMORY_ERROR,
    INTERPRETER_NULL_POINTER
} interpreter_status_t;

interpreter_status_t interpreter_execute_file(const char *filename);
interpreter_status_t interpreter_execute_line(const char *line, int line_number, variables_t *vars);

#endif
