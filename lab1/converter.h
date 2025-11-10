#ifndef CONVERTER_H
#define CONVERTER_H

#include <stddef.h>

typedef enum {
    CONVERT_SUCCESS,
    CONVERT_ERROR_NULL_PTR, 
    CONVERT_ERROR_INVALID_R,
    CONVERT_ERROR_ALLOCATION
} ConverterStatus;

ConverterStatus decimal_to_base(int number, int r, char** result);

#endif