#include <stdio.h>
#include <stdlib.h>
#include "converter.h"

int main(){
    int number;
    int r;
    char* result = NULL;
    ConverterStatus status;

    printf("=== Конвертер из десятичной системы в основание 2^r === \n");
    printf("Введите десятичное число: ");
    if (scanf("%d", &number) != 1){
        printf("\nНужно ввести одно число. Ошибка ввода.");
        return 1;
    }
    printf("\nВведите степень двойки: ");
    if (scanf("%d", &r) != 1){
        printf("\nНужно ввести одно из чисел: 1, 2, 3, 4, 5");
        return 1;
    }

    status = decimal_to_base(number, r, &result);

    int base_system = 2;
    while (r > 0){
        base_system *= 2;
        r--;
    }
    
    switch (status){
        case CONVERT_SUCCESS:
            printf("Результат перевода в %d систему: %s\n", base_system, result);
            break;
        case CONVERT_ERROR_NULL_PTR:
            printf("Передана пустая строка.");
            break;
        case CONVERT_ERROR_INVALID_R:
            printf("Неправильное значение r.\n");
            break;
        case CONVERT_ERROR_ALLOCATION:
            printf("Ошибка распределения памяти.");
            break;
    }

    if (result != NULL){
        free(result);
        result = NULL;
    }

    return 0;
}