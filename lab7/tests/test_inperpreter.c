#include <stdio.h>
#include <assert.h>
#include "variables.h"
#include "operations.h"
#include "parser.h"

void test_variables() {
    variables_t vars;
    assert(variables_init(&vars) == VARIABLES_SUCCESS);
    
    assert(variables_set(&vars, 'A', 42) == VARIABLES_SUCCESS);
    assert(variables_set(&vars, 'Z', 100) == VARIABLES_SUCCESS);
    
    int value;
    assert(variables_get(&vars, 'A', &value) == VARIABLES_SUCCESS);
    assert(value == 42);
    
    assert(variables_get(&vars, 'Z', &value) == VARIABLES_SUCCESS);
    assert(value == 100);
    
    assert(variables_set(&vars, 'a', 1) == VARIABLES_INVALID_NAME);
    assert(variables_set(&vars, '1', 1) == VARIABLES_INVALID_NAME);
    
    assert(variables_get(&vars, 'B', &value) == VARIABLES_INVALID_INDEX);
    
    printf("Variables tests passed!\n");
}

void test_operations() {
    int result;
    
    assert(operations_calculate(5, 3, '+', &result) == OPERATIONS_SUCCESS);
    assert(result == 8);
    
    assert(operations_calculate(5, 3, '-', &result) == OPERATIONS_SUCCESS);
    assert(result == 2);
    
    assert(operations_calculate(5, 3, '*', &result) == OPERATIONS_SUCCESS);
    assert(result == 15);
    
    assert(operations_calculate(6, 3, '/', &result) == OPERATIONS_SUCCESS);
    assert(result == 2);
    
    assert(operations_power(2, 3, &result) == OPERATIONS_SUCCESS);
    assert(result == 8);
    
    assert(operations_power(5, 0, &result) == OPERATIONS_SUCCESS);
    assert(result == 1);
    
    assert(operations_calculate(5, 0, '/', &result) == OPERATIONS_DIVISION_BY_ZERO);
    
    printf("Operations tests passed!\n");
}

void test_parser() {
    variables_t vars;
    variables_init(&vars);
    variables_set(&vars, 'A', 5);
    variables_set(&vars, 'B', 3);
    
    expression_t expr;
    
    assert(parser_parse_line("A = 10", &expr, &vars) == PARSER_SUCCESS);
    assert(expr.operation_type == OP_ASSIGNMENT);
    assert(expr.target_var == 'A');
    assert(expr.is_constant == 1);
    assert(expr.constant_value == 10);
    
    assert(parser_parse_line("C = A", &expr, &vars) == PARSER_SUCCESS);
    assert(expr.operation_type == OP_ASSIGNMENT);
    assert(expr.target_var == 'C');
    assert(expr.is_constant == 0);
    assert(expr.source_var == 'A');
    
    assert(parser_parse_line("D = A + B", &expr, &vars) == PARSER_SUCCESS);
    assert(expr.operation_type == OP_ADDITION);
    assert(expr.operator == '+');
    
    assert(parser_parse_line("print(A)", &expr, &vars) == PARSER_SUCCESS);
    assert(expr.operation_type == OP_PRINT);
    assert(expr.target_var == 'A');
    
    printf("Parser tests passed!\n");
}

int main() {
    test_variables();
    test_operations();
    test_parser();
    
    printf("All tests passed!\n");
    return 0;
}