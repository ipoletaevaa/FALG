#ifndef BRACKET_CHECK_H
#define BRACKET_CHECK_H

#include <stddef.h>

typedef enum {
    BRACKETS_OK,
    BRACKETS_UNBALANCED,
    BRACKETS_INVALID_INPUT,
    BRACKETS_MEMORY_ERROR
} BracketStatus;

BracketStatus check_brackets(const char *str, int *result);

#endif