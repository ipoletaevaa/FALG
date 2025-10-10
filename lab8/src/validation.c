#include "validation.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int is_valid_base(int base) {
    return base >= 2 && base <= 36;
}

int is_valid_number_string(const char* str, int base) {
    if (!str || *str == '\0') {
        return 0;
    }

    const char* ptr = str;
    
    if (*ptr == '-') {
        ptr++;
    }
    
    if (*ptr == '\0') {
        return 0;
    }

    int found_digit = 0;
    
    while (*ptr) {
        char c = *ptr;
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'z') {
            digit = c - 'a' + 10;
        } else {
            return 0;
        }
        
        if (digit >= base) {
            return 0;
        }
        
        found_digit = 1;
        ptr++;
    }

    return found_digit;
}

char* remove_leading_zeros(const char* number) {
    if (!number || *number == '\0') {
        return NULL;
    }

    const char* ptr = number;
    int has_minus = 0;
    
    if (*ptr == '-') {
        has_minus = 1;
        ptr++;
    }
    
    while (*ptr == '0' && *(ptr + 1) != '\0') {
        ptr++;
    }
    
    size_t len = strlen(ptr);
    if (len == 0) {
        char* result = malloc(2);
        if (!result) return NULL;
        strcpy(result, "0");
        return result;
    }
    
    char* result = malloc(len + has_minus + 1);
    if (!result) return NULL;
    
    char* dest = result;
    if (has_minus) {
        *dest++ = '-';
    }
    strcpy(dest, ptr);
    
    return result;
}