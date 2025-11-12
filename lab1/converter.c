#include "converter.h"
#include <stdlib.h>

ConverterStatus decimal_to_base_2r(int number, int r, char** result) {
    if (result == NULL) return CONVERT_ERROR_NULL_PTR;
    if (r < 1 || r > 5) return CONVERT_ERROR_INVALID_R;

    if (number == 0) {
        char* temp = malloc(2);
        if (temp == NULL) return CONVERT_ERROR_ALLOCATION;
        temp[0] = '0';
        temp[1] = '\0';
        *result = temp;
        return CONVERT_SUCCESS;
    }

    unsigned int mask = (1u << r) - 1u;
    unsigned int n;
    int is_negative = 0;

    if (number < 0) {
        is_negative = 1;
        n = (unsigned int)(-number);
    } else {
        n = (unsigned int)number;
    }

    size_t max_len = (32 / r) + 3;
    char* buffer = malloc(max_len);
    if (buffer == NULL) return CONVERT_ERROR_ALLOCATION;

    int index = max_len - 1;
    buffer[index] = '\0';

    while (n > 0) {
        index--;
        unsigned int digit = n & mask;
        
        if (digit < 10) {
            buffer[index] = '0' + digit;
        } else {
            buffer[index] = 'A' + (digit - 10);
        }
        
        n = n >> r;
    }

    if (is_negative) {
        index--;
        buffer[index] = '-';
    }

    char* result_str = malloc(max_len - index);
    if (result_str == NULL) {
        free(buffer);
        return CONVERT_ERROR_ALLOCATION;
    }
    
    char* src = &buffer[index];
    char* dst = result_str;
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
    
    free(buffer);
    *result = result_str;
    return CONVERT_SUCCESS;
}