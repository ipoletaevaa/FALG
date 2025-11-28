#include "parser.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOKENS 100

typedef enum {
    TOKEN_NUMBER,
    TOKEN_VARIABLE,
    TOKEN_OPERATOR,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN
} token_type_t;

typedef struct {
    token_type_t type;
    union {
        int number;
        char variable;
        char operator;
    } value;
} token_t;

static parser_status_t parse_assignment(const char *line, expression_t *expr, variables_t *vars);
static parser_status_t parse_print(const char *line, expression_t *expr, variables_t *vars);
static int get_operator_precedence(char op);
static parser_status_t shunting_yard(const char *expr, token_t *output, int *output_count, variables_t *vars);
static parser_status_t evaluate_rpn(token_t *tokens, int token_count, int *result, variables_t *vars);

parser_status_t parser_parse_line(const char *line, expression_t *expr, variables_t *vars) {
    if (line == NULL || expr == NULL || vars == NULL) {
        return PARSER_NULL_POINTER;
    }
    
    while (isspace(*line)) line++;
    
    if (*line == '\0' || *line == '\n') {
        return PARSER_EMPTY_LINE;
    }
    
    if (strncmp(line, "print", 5) == 0) {
        return parse_print(line, expr, vars);
    }
    
    const char *equals_pos = strchr(line, '=');
    if (equals_pos != NULL) {
        return parse_assignment(line, expr, vars);
    }
    
    return PARSER_INVALID_EXPRESSION;
}

static parser_status_t parse_assignment(const char *line, expression_t *expr, variables_t *vars) {
    const char *equals_pos = strchr(line, '=');
    if (equals_pos == NULL) {
        return PARSER_SYNTAX_ERROR;
    }
    
    const char *var_start = line;
    while (isspace(*var_start)) var_start++;
    
    if (!variables_validate_name(*var_start)) {
        return PARSER_SYNTAX_ERROR;
    }
    
    expr->target_var = *var_start;
    
    const char *expr_start = equals_pos + 1;
    while (isspace(*expr_start)) expr_start++;
    
    token_t rpn_tokens[MAX_TOKENS];
    int token_count = 0;
    
    parser_status_t status = shunting_yard(expr_start, rpn_tokens, &token_count, vars);
    if (status != PARSER_SUCCESS) {
        return status;
    }
    
    int result = 0;
    status = evaluate_rpn(rpn_tokens, token_count, &result, vars);
    if (status != PARSER_SUCCESS) {
        return status;
    }
    
    expr->operation_type = OP_ASSIGNMENT;
    expr->constant_value = result;
    expr->is_constant = 1;
    
    return PARSER_SUCCESS;
}

static parser_status_t parse_print(const char *line, expression_t *expr, variables_t *vars) {
    const char *paren_start = strchr(line, '(');
    const char *paren_end = strchr(line, ')');
    
    if (paren_start == NULL || paren_end == NULL || paren_end < paren_start) {
        return PARSER_SYNTAX_ERROR;
    }
    
    const char *var_ptr = paren_start + 1;
    while (isspace(*var_ptr)) var_ptr++;
    
    char var_name = *var_ptr;
    if (!variables_validate_name(var_name)) {
        return PARSER_SYNTAX_ERROR;
    }
    
    int initialized = 0;
    variables_status_t status = variables_is_initialized(vars, var_name, &initialized);
    if (status != VARIABLES_SUCCESS || !initialized) {
        return PARSER_UNINITIALIZED_VARIABLE;
    }
    
    expr->operation_type = OP_PRINT;
    expr->target_var = var_name;
    
    return PARSER_SUCCESS;
}

static int get_operator_precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*': case '/': return 2;
        case '+': case '-': return 1;
        default: return 0;
    }
}

static parser_status_t shunting_yard(const char *expr, token_t *output, int *output_count, variables_t *vars) {
    token_t operator_stack[MAX_TOKENS];
    int op_stack_top = -1;
    *output_count = 0;
    
    const char *ptr = expr;
    while (*ptr && *ptr != '\n') {
        while (isspace(*ptr)) ptr++;
        if (*ptr == '\0' || *ptr == '\n') break;
        
        if (isdigit(*ptr)) {
            int num = 0;
            while (isdigit(*ptr)) {
                num = num * 10 + (*ptr - '0');
                ptr++;
            }
            output[(*output_count)++].type = TOKEN_NUMBER;
            output[*output_count - 1].value.number = num;
        }
        else if (variables_validate_name(*ptr)) {
            int initialized = 0;
            variables_status_t status = variables_is_initialized(vars, *ptr, &initialized);
            if (status != VARIABLES_SUCCESS || !initialized) {
                return PARSER_UNINITIALIZED_VARIABLE;
            }
            output[(*output_count)++].type = TOKEN_VARIABLE;
            output[*output_count - 1].value.variable = *ptr;
            ptr++;
        }
        else if (*ptr == '(') {
            operator_stack[++op_stack_top].type = TOKEN_LEFT_PAREN;
            ptr++;
        }
        else if (*ptr == ')') {
            while (op_stack_top >= 0 && operator_stack[op_stack_top].type != TOKEN_LEFT_PAREN) {
                output[(*output_count)++] = operator_stack[op_stack_top--];
            }
            if (op_stack_top < 0) {
                return PARSER_SYNTAX_ERROR;
            }
            op_stack_top--;
            ptr++;
        }
        else if (strchr("+-*/^", *ptr) != NULL) {
            token_t op_token;
            op_token.type = TOKEN_OPERATOR;
            op_token.value.operator = *ptr;
            
            int current_prec = get_operator_precedence(*ptr);
            
            while (op_stack_top >= 0) {
                token_t top = operator_stack[op_stack_top];
                if (top.type != TOKEN_OPERATOR) break;
                
                int top_prec = get_operator_precedence(top.value.operator);
                if (current_prec <= top_prec) {
                    output[(*output_count)++] = operator_stack[op_stack_top--];
                } else {
                    break;
                }
            }
            
            operator_stack[++op_stack_top] = op_token;
            ptr++;
        }
        else {
            return PARSER_SYNTAX_ERROR;
        }
    }
    
    while (op_stack_top >= 0) {
        if (operator_stack[op_stack_top].type == TOKEN_LEFT_PAREN) {
            return PARSER_SYNTAX_ERROR;
        }
        output[(*output_count)++] = operator_stack[op_stack_top--];
    }
    
    return PARSER_SUCCESS;
}

static parser_status_t evaluate_rpn(token_t *tokens, int token_count, int *result, variables_t *vars) {
    int stack[MAX_TOKENS];
    int stack_top = -1;
    
    for (int i = 0; i < token_count; i++) {
        token_t token = tokens[i];
        
        if (token.type == TOKEN_NUMBER) {
            stack[++stack_top] = token.value.number;
        }
        else if (token.type == TOKEN_VARIABLE) {
            int value;
            variables_status_t status = variables_get(vars, token.value.variable, &value);
            if (status != VARIABLES_SUCCESS) {
                return PARSER_UNINITIALIZED_VARIABLE;
            }
            stack[++stack_top] = value;
        }
        else if (token.type == TOKEN_OPERATOR) {
            if (stack_top < 1) {
                return PARSER_SYNTAX_ERROR;
            }
            
            int right = stack[stack_top--];
            int left = stack[stack_top--];
            int res = 0;
            
            operations_status_t op_status = operations_calculate(left, right, token.value.operator, &res);
            if (op_status != OPERATIONS_SUCCESS) {
                return PARSER_SYNTAX_ERROR;
            }
            
            stack[++stack_top] = res;
        }
    }
    
    if (stack_top != 0) {
        return PARSER_SYNTAX_ERROR;
    }
    
    *result = stack[stack_top];
    return PARSER_SUCCESS;
}

parser_status_t parser_evaluate_expression(const expression_t *expr, const variables_t *vars, int *result) {
    if (expr == NULL || vars == NULL || result == NULL) {
        return PARSER_NULL_POINTER;
    }
    
    switch (expr->operation_type) {
        case OP_ASSIGNMENT:
            *result = expr->constant_value;
            break;
            
        case OP_PRINT: {
            variables_status_t status = variables_get(vars, expr->target_var, result);
            if (status != VARIABLES_SUCCESS) {
                return PARSER_UNINITIALIZED_VARIABLE;
            }
            break;
        }
            
        default:
            return PARSER_INVALID_EXPRESSION;
    }
    
    return PARSER_SUCCESS;
}