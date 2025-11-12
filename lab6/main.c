#include <stdio.h>
#include <string.h>
#include "bracket_check.h"

#define MAX_INPUT_LENGTH 1000

int main() {
    char input[MAX_INPUT_LENGTH + 1];
    int result;
    BracketStatus status;
    
    printf("Введите строку для проверки скобок (максимум %d символов):\n", MAX_INPUT_LENGTH);
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Ошибка чтения ввода\n");
        return 1;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    status = check_brackets(input, &result);
    
    switch (status) {
        case BRACKETS_OK:
            if (result) {
                printf("Строка содержит корректную расстановку скобок\n");
            } else {
                printf("Строка содержит некорректную расстановку скобок\n");
            }
            break;
            
        case BRACKETS_INVALID_INPUT:
            printf("Ошибка: неверные входные параметры\n");
            break;
            
        case BRACKETS_MEMORY_ERROR:
            printf("Ошибка: недостаточно памяти\n");
            break;
            
        default:
            printf("Неизвестная ошибка\n");
            break;
    }
    
    return 0;
}