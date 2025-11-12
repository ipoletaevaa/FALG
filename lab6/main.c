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

}