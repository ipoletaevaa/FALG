#include "number_processor.h"
#include "validation.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int char_to_digit(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    }
    return -1;
}

static int find_max_digit(const char* number_str) {
    int max_digit = 0;
    for (size_t i = 0; number_str[i] != '\0'; i++) {
        int digit = char_to_digit(number_str[i]);
        if (digit > max_digit) {
            max_digit = digit;
        }
    }
    return max_digit;
}

ProcessorStatus find_min_base(const char* number_str, int* min_base) {
    if (!number_str || !min_base) {
        return PROCESSOR_INVALID_INPUT;
    }
    
    if (!is_valid_number_string(number_str)) {
        return PROCESSOR_INVALID_NUMBER;
    }
    
    int max_digit = find_max_digit(number_str);
    *min_base = (max_digit < 1) ? 2 : max_digit + 1;
    
    if (*min_base < 2 || *min_base > 36) {
        return PROCESSOR_INVALID_NUMBER;
    }
    
    return PROCESSOR_SUCCESS;
}

ProcessorStatus convert_to_decimal(const char* number_str, int base, long long* result) {
    if (!number_str || !result || base < 2 || base > 36) {
        return PROCESSOR_INVALID_INPUT;
    }
    
    if (!is_valid_number_string(number_str)) {
        return PROCESSOR_INVALID_NUMBER;
    }
    
    size_t len = strlen(number_str);
    if (len > 20) {
        return PROCESSOR_OVERFLOW;
    }
    
    unsigned long long value = 0;
    
    for (size_t i = 0; number_str[i] != '\0'; i++) {
        int digit = char_to_digit(number_str[i]);
        if (digit < 0 || digit >= base) {
            return PROCESSOR_INVALID_NUMBER;
        }

        if (value > ULLONG_MAX / base) {
            return PROCESSOR_OVERFLOW;
        }
        
        unsigned long long new_value = value * base;
        
        if (new_value > ULLONG_MAX - digit) {
            return PROCESSOR_OVERFLOW;
        }
        
        value = new_value + digit;
        
        if (value > LLONG_MAX) {
            return PROCESSOR_OVERFLOW;
        }
    }
    
    *result = (long long)value;
    return PROCESSOR_SUCCESS;
}

ProcessorStatus process_number(const char* number_str, NumberResult* result) {
    if (!number_str || !result) {
        return PROCESSOR_INVALID_INPUT;
    }
    
    result->original_number = NULL;
    result->min_base = 0;
    result->decimal_value = 0;
    
    char* cleaned_number = remove_leading_zeros(number_str);
    if (!cleaned_number) {
        return PROCESSOR_MEMORY_ERROR;
    }
    
    ProcessorStatus status = find_min_base(cleaned_number, &result->min_base);
    if (status != PROCESSOR_SUCCESS) {
        free(cleaned_number);
        return status;
    }
    
    status = convert_to_decimal(cleaned_number, result->min_base, &result->decimal_value);
    if (status != PROCESSOR_SUCCESS) {
        free(cleaned_number);
        return status;
    }
    
    result->original_number = cleaned_number;
    return PROCESSOR_SUCCESS;
}

void cleanup_number_result(NumberResult* result) {
    if (result && result->original_number) {
        free(result->original_number);
        result->original_number = NULL;
    }
}