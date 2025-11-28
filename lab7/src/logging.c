#include "logging.h"
#include <stdio.h>
#include <string.h>

static FILE *log_file = NULL;

logging_status_t logging_init(const char *filename) {
    if (filename == NULL) {
        return LOGGING_NULL_POINTER;
    }
    
    log_file = fopen(filename, "w");
    if (log_file == NULL) {
        return LOGGING_FILE_ERROR;
    }
    
    return LOGGING_SUCCESS;
}

logging_status_t logging_close(void) {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
    
    return LOGGING_SUCCESS;
}

logging_status_t logging_write_entry(int line_number, const char *original_line, 
                                   const variables_t *vars, operation_type_t op_type) {
    if (original_line == NULL || vars == NULL) {
        return LOGGING_NULL_POINTER;
    }
    
    if (log_file == NULL) {
        return LOGGING_FILE_ERROR;
    }
    
    char clean_line[256];
    strncpy(clean_line, original_line, sizeof(clean_line) - 1);
    clean_line[sizeof(clean_line) - 1] = '\0';
    
    char *newline_pos = strchr(clean_line, '\n');
    if (newline_pos != NULL) {
        *newline_pos = '\0';
    }
    
    char variables_str[512];
    variables_status_t var_status = variables_get_all_initialized(vars, variables_str, sizeof(variables_str));
    if (var_status != VARIABLES_SUCCESS) {
        strcpy(variables_str, "error");
    }
    
    const char *operation_desc = operations_type_to_string(op_type);
    
    fprintf(log_file, "[%d] %s | %s | %s\n", 
            line_number, clean_line, variables_str, operation_desc);
    fflush(log_file);
    
    return LOGGING_SUCCESS;
}