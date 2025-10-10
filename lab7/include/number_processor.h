#ifndef NUMBER_PROCESSOR_H
#define NUMBER_PROCESSOR_H

#include <stddef.h>

typedef enum {
    PROCESSOR_SUCCESS = 0,
    PROCESSOR_INVALID_INPUT = 1,
    PROCESSOR_MEMORY_ERROR = 2,
    PROCESSOR_INVALID_NUMBER = 3,
    PROCESSOR_OVERFLOW = 4
} ProcessorStatus;

typedef struct {
    char* original_number;
    int min_base;
    long long decimal_value;
} NumberResult;

ProcessorStatus find_min_base(const char* number_str, int* min_base);
ProcessorStatus convert_to_decimal(const char* number_str, int base, long long* result);
ProcessorStatus process_number(const char* number_str, NumberResult* result);
void cleanup_number_result(NumberResult* result);

#endif