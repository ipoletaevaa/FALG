#ifndef NUMBER_CONVERTER_H
#define NUMBER_CONVERTER_H

#include <limits.h>

typedef enum {
    CONVERTER_SUCCESS,
    CONVERTER_INVALID_INPUT,
    CONVERTER_MEMORY_ERROR,
    CONVERTER_OVERFLOW
} ConverterStatus;

ConverterStatus convert_to_base(long long number, int base, char** result);
ConverterStatus parse_number(const char* str, int base, long long* result);
char* remove_leading_zeros(const char* number);

#endif