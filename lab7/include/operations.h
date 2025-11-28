#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "variables.h"

typedef enum {
    OPERATIONS_SUCCESS = 0,
    OPERATIONS_DIVISION_BY_ZERO,
    OPERATIONS_OVERFLOW,
    OPERATIONS_INVALID_OPERATOR,
    OPERATIONS_NULL_POINTER
} operations_status_t;

typedef enum {
    OP_ASSIGNMENT,
    OP_ADDITION,
    OP_SUBTRACTION,
    OP_MULTIPLICATION,
    OP_DIVISION,
    OP_POWER,
    OP_PRINT
} operation_type_t;

operations_status_t operations_calculate(int left, int right, char operator, int *result);
operations_status_t operations_power(int base, int exponent, int *result);
const char* operations_type_to_string(operation_type_t type);

#endif