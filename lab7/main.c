#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"
#include "validation.h"

int main(int argc, char** argv) {
    ValidationStatus validation_status = validate_command_line_args(argc, argv);
    if (validation_status != VALIDATION_SUCCESS) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    
    if (validate_filenames_different(argv[1], argv[2]) != VALIDATION_SUCCESS) {
        fprintf(stderr, "Error: Input and output files cannot be the same\n");
        return 1;
    }
    
    FileStatus file_status = process_input_file(argv[1], argv[2]);
    
    if (file_status != FILE_SUCCESS) {
        fprintf(stderr, "Error processing files\n");
        return 1;
    }
    
    printf("File processed successfully\n");
    return 0;
}