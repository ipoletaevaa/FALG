#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

interpreter_status_t interpreter_execute_file(const char *filename) {
    if (filename == NULL) {
        return INTERPRETER_NULL_POINTER;
    }
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return INTERPRETER_FILE_ERROR;
    }
    
    logging_status_t log_status = logging_init("trace.log");
    if (log_status != LOGGING_SUCCESS) {
        fclose(file);
        return INTERPRETER_FILE_ERROR;
    }
    
    variables_t vars;
    variables_status_t var_status = variables_init(&vars);
    if (var_status != VARIABLES_SUCCESS) {
        fclose(file);
        logging_close();
        return INTERPRETER_MEMORY_ERROR;
    }
    
    char line[256];
    int line_number = 1;
    
    while (fgets(line, sizeof(line), file) != NULL) {
        interpreter_status_t status = interpreter_execute_line(line, line_number, &vars);
        
        if (status != INTERPRETER_SUCCESS && status != INTERPRETER_SYNTAX_ERROR) {
            fclose(file);
            logging_close();
            return status;
        }
        
        line_number++;
    }
    
    fclose(file);
    logging_close();
    return INTERPRETER_SUCCESS;
}

interpreter_status_t interpreter_execute_line(const char *line, int line_number, variables_t *vars) {
    if (line == NULL || vars == NULL) {
        return INTERPRETER_NULL_POINTER;
    }
    
    expression_t expr;
    parser_status_t parse_status = parser_parse_line(line, &expr, vars);
    
    if (parse_status == PARSER_EMPTY_LINE) {
        return INTERPRETER_SUCCESS;
    }
    
    if (parse_status != PARSER_SUCCESS) {
        logging_write_entry(line_number, line, vars, OP_ASSIGNMENT);
        return INTERPRETER_SYNTAX_ERROR;
    }
    
    int result = 0;
    parse_status = parser_evaluate_expression(&expr, vars, &result);
    
    if (parse_status != PARSER_SUCCESS) {
        logging_write_entry(line_number, line, vars, expr.operation_type);
        return INTERPRETER_SYNTAX_ERROR;
    }
    
    switch (expr.operation_type) {
        case OP_ASSIGNMENT:
            variables_set(vars, expr.target_var, result);
            break;
            
        case OP_ADDITION:
        case OP_SUBTRACTION:
        case OP_MULTIPLICATION:
        case OP_DIVISION:
        case OP_POWER:
            variables_set(vars, expr.target_var, result);
            break;
            
        case OP_PRINT:
            printf("%d\n", result);
            break;
    }
    
    logging_write_entry(line_number, line, vars, expr.operation_type);
    
    return INTERPRETER_SUCCESS;
}
