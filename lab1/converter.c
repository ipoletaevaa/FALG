#include "converter.h"
#include <stdlib.h>
#include <stdbool.h>

ConverterStatus decimal_to_base(int number, int r, char** result){
    if (result == NULL){
        return CONVERT_ERROR_NULL_PTR;
    }

    if (r < 1 || r > 5){
        return CONVERT_ERROR_INVALID_R;
    }

    if (number == 0){
        char* temp = (char*)malloc(2 * sizeof(char));
        if (temp == NULL) {
            return CONVERT_ERROR_ALLOCATION;
        }
        temp[0] = '0';
        temp[1] = '\n';
        *result = temp;
        return CONVERT_SUCCESS;
    }

    unsigned int mask = (1u << r) - 1u; //00000111 для 8
    unsigned int n;
    bool is_negative = false;

    if (number < 0){
        is_negative = true;
        n = (unsigned int)(-number);
    }else{
        n = (unsigned int)number;
    }

    char buffer[64];
    int index = 63;
    buffer[index] = '\0';

    while (n > 0 && index > 0){
        index--;
        unsigned int digit = n & mask;

        if (digit < 10){
            buffer[index] = '0' + digit;
        }else{
            buffer[index] = 'A' + (digit - 10);
        }
    }

    n = n >> r;

    if (is_negative && index > 0){
        index--;
        buffer[index] = '-';
    }

    char* result_str = (char*)malloc(64 - index);
    if (result_str == NULL){
        return CONVERT_ERROR_ALLOCATION;
    }
    
    char* src = &buffer[index];
    char* dst = result_str;
    while (*src){
        *dst++ = *src++;
    }

    *result = result_str;
    return CONVERT_SUCCESS;
}