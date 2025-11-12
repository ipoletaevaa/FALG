#include "bracket_check.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t capacity;
    size_t size;
} Stack;

static Stack* stack_create(size_t initial_capacity) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) return NULL;
    
    stack->data = (char*)malloc(initial_capacity * sizeof(char));
    if (!stack->data) {
        free(stack);
        return NULL;
    }
    
    stack->capacity = initial_capacity;
    stack->size = 0;
    return stack;
}

static void stack_destroy(Stack *stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

static int stack_resize(Stack *stack, size_t new_capacity) {
    char *new_data = (char*)realloc(stack->data, new_capacity * sizeof(char));
    if (!new_data) return 0;
    
    stack->data = new_data;
    stack->capacity = new_capacity;
    return 1;
}

static int stack_push(Stack *stack, char value) {
    if (stack->size >= stack->capacity) {
        if (!stack_resize(stack, stack->capacity * 2)) {
            return 0;
        }
    }
    
    stack->data[stack->size++] = value;
    return 1;
}

static int stack_pop(Stack *stack, char *value) {
    if (stack->size == 0) return 0;
    
    *value = stack->data[--stack->size];
    return 1;
}

static int stack_is_empty(const Stack *stack) {
    return stack->size == 0;
}

static int is_open_bracket(char c) {
    return c == '(' || c == '[' || c == '{' || c == '<';
}

static int is_close_bracket(char c) {
    return c == ')' || c == ']' || c == '}' || c == '>';
}

static char get_matching_open_bracket(char close_bracket) {
    switch (close_bracket) {
        case ')': return '(';
        case ']': return '[';
        case '}': return '{';
        case '>': return '<';
        default: return '\0';
    }
}

BracketStatus check_brackets(const char *str, int *result) {
    if (str == NULL || result == NULL) {
        return BRACKETS_INVALID_INPUT;
    }
    
    Stack *stack = stack_create(16);
    if (!stack) {
        return BRACKETS_MEMORY_ERROR;
    }
    
    *result = 1;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        char current = str[i];
        
        if (is_open_bracket(current)) {
            if (!stack_push(stack, current)) {
                stack_destroy(stack);
                return BRACKETS_MEMORY_ERROR;
            }
        } 
        else if (is_close_bracket(current)) {
            char expected_open = get_matching_open_bracket(current);
            char actual_open;
            
            if (!stack_pop(stack, &actual_open)) {
                *result = 0;
                break;
            }
            
            if (actual_open != expected_open) {
                *result = 0;
                break;
            }
        }
    }
    
    if (*result == 1 && !stack_is_empty(stack)) {
        *result = 0;
    }
    
    stack_destroy(stack);
    return BRACKETS_OK;
}