#include "operations.h"
#include <limits.h>
#include <string.h>

operations_status_t operations_calculate(int left, int right, char operator, int *result) {
    if (result == NULL) {
        return OPERATIONS_NULL_POINTER;
    }
    
    switch (operator) {
        case '+':
            if ((right > 0 && left > INT_MAX - right) || 
                (right < 0 && left < INT_MIN - right)) {
                return OPERATIONS_OVERFLOW;
            }
            *result = left + right;
            break;
            
        case '-':
            if ((right > 0 && left < INT_MIN + right) || 
                (right < 0 && left > INT_MAX + right)) {
                return OPERATIONS_OVERFLOW;
            }
            *result = left - right;
            break;
            
        case '*':
            if (left > 0) {
                if (right > 0 && left > INT_MAX / right) return OPERATIONS_OVERFLOW;
                if (right < 0 && right < INT_MIN / left) return OPERATIONS_OVERFLOW;
            } else if (left < 0) {
                if (right > 0 && left < INT_MIN / right) return OPERATIONS_OVERFLOW;
                if (right < 0 && right < INT_MAX / left) return OPERATIONS_OVERFLOW;
            }
            *result = left * right;
            break;
            
        case '/':
            if (right == 0) {
                return OPERATIONS_DIVISION_BY_ZERO;
            }
            *result = left / right;
            break;
            
        case '^':
            return operations_power(left, right, result);
            
        default:
            return OPERATIONS_INVALID_OPERATOR;
    }
    
    return OPERATIONS_SUCCESS;
}

operations_status_t operations_power(int base, int exponent, int *result) {
    if (result == NULL) {
        return OPERATIONS_NULL_POINTER;
    }
    
    if (exponent < 0) {
        return OPERATIONS_INVALID_OPERATOR;
    }
    
    if (exponent == 0) {
        *result = 1;
        return OPERATIONS_SUCCESS;
    }
    
    int res = 1;
    int temp_base = base;
    int temp_exp = exponent;
    
    while (temp_exp > 0) {
        if (temp_exp % 2 == 1) {
            if (res > INT_MAX / temp_base) {
                return OPERATIONS_OVERFLOW;
            }
            res *= temp_base;
        }
        
        temp_exp /= 2;
        if (temp_exp > 0) {
            if (temp_base > INT_MAX / temp_base) {
                return OPERATIONS_OVERFLOW;
            }
            temp_base *= temp_base;
        }
    }
    
    *result = res;
    return OPERATIONS_SUCCESS;
}

const char* operations_type_to_string(operation_type_t type) {
    switch (type) {
        case OP_ASSIGNMENT: return "Assignment";
        case OP_ADDITION: return "Arithmetic operation";
        case OP_SUBTRACTION: return "Arithmetic operation";
        case OP_MULTIPLICATION: return "Arithmetic operation";
        case OP_DIVISION: return "Arithmetic operation";
        case OP_POWER: return "Arithmetic operation";
        case OP_PRINT: return "Print";
        default: return "Unknown";
    }
}