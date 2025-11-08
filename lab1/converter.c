#include "converter.h"
#include <stdlib.h>
#include <stdbool.h>

ConverterStatus decimal_to_base_2r(int number, int r, char** result, double epsilon){
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

}

