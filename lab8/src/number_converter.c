#include "number_converter.h"
#include "validation.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static char digit_to_char(int digit) {
    if (digit >= 0 && digit <= 9) {
        return '0' + digit;
    } else {
        return 'A' + (digit - 10);
    }
}

static int char_to_digit(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    } else if (c >= 'a' && c <= 'z') { 
        return c - 'a' + 10;
    } else {
        return -1;
    }
}

ConverterStatus convert_to_base(long long number, int base, char** result) {
    if (base < 2 || base > 36 || !result) {
        return CONVERTER_INVALID_INPUT;
    }

    if (number == 0) {
        *result = malloc(2);
        if (!*result) return CONVERTER_MEMORY_ERROR;
        strcpy(*result, "0");
        return CONVERTER_SUCCESS;
    }

    int is_negative = (number < 0);
    long long n = is_negative ? -number : number;

    int length = 0;
    long long temp = n;
    while (temp > 0) {
        temp /= base;
        length++;
    }
    if (is_negative) length++;

    *result = malloc(length + 1);
    if (!*result) return CONVERTER_MEMORY_ERROR;

    int index = length;
    (*result)[index] = '\0';
    
    do {
        int digit = n % base;
        (*result)[--index] = digit_to_char(digit);
        n /= base;
    } while (n > 0);

    if (is_negative) {
        (*result)[--index] = '-';
    }

    return CONVERTER_SUCCESS;
}

ConverterStatus parse_number(const char* str, int base, long long* result) {
    if (!str || !result || base < 2 || base > 36) {
        return CONVERTER_INVALID_INPUT;
    }

    if (!is_valid_number_string(str, base)) {
        return CONVERTER_INVALID_INPUT;
    }

    int is_negative = 0;
    const char* ptr = str;

    if (*ptr == '-') {
        is_negative = 1;
        ptr++;
    }

    long long value = 0;
    while (*ptr) {
        int digit = char_to_digit(*ptr);
        if (digit < 0 || digit >= base) {
            return CONVERTER_INVALID_INPUT;
        }

        if (value > (LLONG_MAX - digit) / base) {
            return CONVERTER_OVERFLOW;
        }

        value = value * base + digit;
        ptr++;
    }

    *result = is_negative ? -value : value;
    return CONVERTER_SUCCESS;
}
