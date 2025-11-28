#ifndef PARSER_H
#define PARSER_H

#include "variables.h"
#include "operations.h"

typedef enum {
    PARSER_SUCCESS = 0,
    PARSER_SYNTAX_ERROR,
    PARSER_UNKNOWN_VARIABLE,
    PARSER_UNINITIALIZED_VARIABLE,
    PARSER_INVALID_EXPRESSION,
    PARSER_EMPTY_LINE,
    PARSER_NULL_POINTER
} parser_status_t;

typedef struct {
    char target_var;
    char source_var;
    int constant_value;
    char operator;
    operation_type_t operation_type;
    int is_constant;
} expression_t;

parser_status_t parser_parse_line(const char *line, expression_t *expr, variables_t *vars);
parser_status_t parser_evaluate_expression(const expression_t *expr, const variables_t *vars, int *result);

#endif