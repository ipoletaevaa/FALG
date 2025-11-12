#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "converter.h"

void test_zero() {
    char* result = NULL;
    ConverterStatus status = decimal_to_base_2r(0, 2, &result);
    assert(status == CONVERT_SUCCESS);
    assert(strcmp(result, "0") == 0);
    free(result);
    printf("Тест нуля: пройден\n");
}

void test_positive_binary() {
    char* result = NULL;
    ConverterStatus status = decimal_to_base_2r(42, 1, &result);
    assert(status == CONVERT_SUCCESS);
    assert(strcmp(result, "101010") == 0);
    free(result);
    printf("Тест 42 в двоичной: пройден\n");
}

void test_positive_octal() {
    char* result = NULL;
    ConverterStatus status = decimal_to_base_2r(42, 3, &result);
    assert(status == CONVERT_SUCCESS);
    assert(strcmp(result, "52") == 0);
    free(result);
    printf("Тест 42 в восьмеричной: пройден\n");
}

void test_negative_number() {
    char* result = NULL;
    ConverterStatus status = decimal_to_base_2r(-42, 1, &result);
    assert(status == CONVERT_SUCCESS);
    assert(result[0] == '-');
    free(result);
    printf("Тест отрицательного числа: пройден\n");
}

void test_invalid_r() {
    char* result = NULL;
    ConverterStatus status = decimal_to_base_2r(10, 6, &result);
    assert(status == CONVERT_ERROR_INVALID_R);
    printf("Тест неверного r: пройден\n");
}

int main() {
    printf("Запуск автоматических тестов...\n\n");
    
    test_zero();
    test_positive_binary();
    test_positive_octal();
    test_negative_number();
    test_invalid_r();
    
    printf("\nВсе тесты пройдены успешно!\n");
    return 0;
}