#ifndef VALIDATION_H
#define VALIDATION_H

#include <stddef.h>
#include <limits.h>

typedef enum {
    VALIDATION_SUCCESS = 0,
    VALIDATION_INVALID_INPUT = 1,
    VALIDATION_MEMORY_ERROR = 2,
    VALIDATION_INVALID_CHARACTER = 3,
    VALIDATION_SAME_FILES = 4
} ValidationStatus;

int is_valid_number_string(const char* str);
char* remove_leading_zeros(const char* number_str);
int is_whitespace(char c);
ValidationStatus validate_command_line_args(int argc, char** argv);
ValidationStatus validate_filenames_different(const char* filename1, const char* filename2);

#endif