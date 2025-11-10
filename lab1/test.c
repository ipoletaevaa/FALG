#include <stdio.h>
#include <stdlib.h>
#include "converter.h"

int main() {
    int number;
    int r;
    char* result = NULL;
    ConverterStatus status;
    
    printf("=== Конвертер из десятичной системы в основание 2^r ===\n");
    printf("Введите десятичное число: ");
    
    if (scanf("%d", &number) != 1) {
        printf("Ошибка: Неверный ввод для десятичного числа.\n");
        return EXIT_FAILURE;
    }
    
    printf("Введите показатель r (1-5): ");
    if (scanf("%d", &r) != 1) {
        printf("Ошибка: Неверный ввод для показателя r.\n");
        return EXIT_FAILURE;
    }
    
    status = decimal_to_base(number, r, &result);
    
    switch (status) {
        case CONVERT_SUCCESS:
            printf("Результат: %d (основание 10) = %s (основание 2^%d)\n", number, result, r);
            break;
        case CONVERT_ERROR_NULL_PTR:
            printf("Ошибка: Нулевой указатель.\n");
            break;
        case CONVERT_ERROR_INVALID_R:
            printf("Ошибка: Показатель r должен быть между 1 и 5.\n");
            break;
        case CONVERT_ERROR_ALLOCATION:
            printf("Ошибка: Не удалось выделить память.\n");
            break;
        default:
            printf("Произошла неизвестная ошибка.\n");
            break;
    }
    
    if (result != NULL) {
        free(result);
    }
    
    return (status == CONVERT_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}