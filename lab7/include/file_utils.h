#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "number_processor.h"

typedef enum {
    FILE_SUCCESS = 0,
    FILE_OPEN_ERROR = 1,
    FILE_READ_ERROR = 2,
    FILE_WRITE_ERROR = 3,
    FILE_MEMORY_ERROR = 4
} FileStatus;

FileStatus process_input_file(const char* input_filename, const char* output_filename);

#endif