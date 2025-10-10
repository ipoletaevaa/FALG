#include "input_processor.h"
#include "number_converter.h"
#include "validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <strings.h> 

ProcessorStatus process_user_input(int base, long long* max_number, char** max_number_str) {
    if (!max_number || !max_number_str || !is_valid_base(base)) {
        return PROCESSOR_INVALID_INPUT;
    }

    *max_number = 0;
    *max_number_str = NULL;
    
    char buffer[256];
    long long current_max = 0;
    char* current_max_str = NULL;
    int numbers_found = 0;

    printf("Введите числа в системе с основанием %d (для завершения введите 'Stop'):\n", base);

    while (1) {
        printf("> ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (strcasecmp(buffer, "Stop") == 0) {
             break;
        }

        if (buffer[0] == '\0') {
            continue;
        }

        long long number;
        ConverterStatus status = parse_number(buffer, base, &number);
        
        if (status != CONVERTER_SUCCESS) {
            printf("Ошибка: некорректное число '%s'\n", buffer);
            continue;
        }

        long long abs_number = llabs(number);
        long long abs_current_max = llabs(current_max);

        if (!numbers_found || abs_number > abs_current_max) {
            current_max = number;
            free(current_max_str);
            current_max_str = malloc(strlen(buffer) + 1);
            if (current_max_str) {
                strcpy(current_max_str, buffer);
            }
            if (!current_max_str) {
                return PROCESSOR_MEMORY_ERROR;
            }
        }
        
        numbers_found++;
    }

    if (current_max_str) {
        *max_number = current_max;
        *max_number_str = current_max_str;
        return PROCESSOR_SUCCESS;
    } else {
        return PROCESSOR_STOP_SIGNAL;
    }
}