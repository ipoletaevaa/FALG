#include "file_utils.h"
#include "validation.h"
#include "number_processor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_BUFFER_SIZE 64

static FileStatus read_next_number(FILE* file, char** buffer, size_t* buffer_size) {
    if (!file || !buffer || !buffer_size) {
        return FILE_READ_ERROR;
    }
    
    if (*buffer == NULL) {
        *buffer_size = INITIAL_BUFFER_SIZE;
        *buffer = malloc(*buffer_size);
        if (!*buffer) {
            return FILE_READ_ERROR;
        }
    }
    
    int c;
    size_t index = 0;
    
    while ((c = fgetc(file)) != EOF) {
        if (!is_whitespace(c)) {
            if (index >= *buffer_size - 1) {
                *buffer_size *= 2;
                char* new_buffer = realloc(*buffer, *buffer_size);
                if (!new_buffer) {
                    free(*buffer);
                    *buffer = NULL;
                    return FILE_READ_ERROR;
                }
                *buffer = new_buffer;
            }
            
            (*buffer)[index++] = (char)c;
        } else if (index > 0) {
            break;
        }
    }
    
    if (index == 0 && c == EOF) {
        return FILE_READ_ERROR;
    }
    
    (*buffer)[index] = '\0';
    return FILE_SUCCESS;
}

FileStatus process_input_file(const char* input_filename, const char* output_filename) {
    if (!input_filename || !output_filename) {
        return FILE_OPEN_ERROR;
    }

    if (strcmp(input_filename, output_filename) == 0) {
        fprintf(stderr, "Error: Input and output files cannot be the same\n");
        return FILE_OPEN_ERROR;
    }
    
    FILE* input_file = fopen(input_filename, "r");
    if (!input_file) {
        return FILE_OPEN_ERROR;
    }
    
    FILE* output_file = fopen(output_filename, "w");
    if (!output_file) {
        fclose(input_file);
        return FILE_OPEN_ERROR;
    }
    
    char* number_buffer = NULL;
    size_t buffer_size = 0;
    FileStatus file_status = FILE_SUCCESS;
    
    while (file_status == FILE_SUCCESS) {
        file_status = read_next_number(input_file, &number_buffer, &buffer_size);
        
        if (file_status == FILE_SUCCESS) {
            if (is_valid_number_string(number_buffer)) {
                NumberResult result;
                ProcessorStatus proc_status = process_number(number_buffer, &result);
                
                if (proc_status == PROCESSOR_SUCCESS) {
                    fprintf(output_file, "%s %d %lld\n", 
                           result.original_number, 
                           result.min_base, 
                           result.decimal_value);
                } else if (proc_status == PROCESSOR_OVERFLOW) {
                    fprintf(output_file, "%s %d overflow\n", number_buffer, result.min_base);
                } else {
                    fprintf(stderr, "Warning: Skipping invalid number '%s'\n", number_buffer);
                }
                
                cleanup_number_result(&result);
            } else if (strlen(number_buffer) > 0) {
                fprintf(stderr, "Warning: Skipping invalid string '%s'\n", number_buffer);
            }
        }
    }
    
    free(number_buffer);
    fclose(input_file);
    fclose(output_file);
    
    return FILE_SUCCESS;
}