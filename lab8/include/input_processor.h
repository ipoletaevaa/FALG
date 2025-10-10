#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

typedef enum {
    PROCESSOR_SUCCESS = 0,
    PROCESSOR_INVALID_INPUT = 1,
    PROCESSOR_MEMORY_ERROR = 2,
    PROCESSOR_STOP_SIGNAL = 3
} ProcessorStatus;

ProcessorStatus process_user_input(int base, long long* max_number, char** max_number_str);

#endif