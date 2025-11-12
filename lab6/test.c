#include <stdio.h>
#include <assert.h>
#include "bracket_check.h"

void run_tests() {
    int result;
    BracketStatus status;
    
    printf("Запуск тестов...\n");
    
    status = check_brackets("(a + b) * [c - d] / {e % f} + <g & h>", &result);
    assert(status == BRACKETS_OK && result == 1);
    printf("Тест 1 пройден\n");
    
    status = check_brackets("({[<>]})", &result);
    assert(status == BRACKETS_OK && result == 1);
    printf("Тест 2 пройден\n");
    
    status = check_brackets("(a + b [ c - d ) ]", &result);
    assert(status == BRACKETS_OK && result == 0);
    printf("Тест 3 пройден\n");
    
    status = check_brackets("a + b)", &result);
    assert(status == BRACKETS_OK && result == 0);
    printf("Тест 4 пройден\n");
    
    status = check_brackets("(a + b", &result);
    assert(status == BRACKETS_OK && result == 0);
    printf("Тест 5 пройден\n");
    
    status = check_brackets("", &result);
    assert(status == BRACKETS_OK && result == 1);
    printf("Тест 6 пройден\n");
    
    status = check_brackets("Hello World 123!", &result);
    assert(status == BRACKETS_OK && result == 1);
    printf("Тест 7 пройден\n");
    
    status = check_brackets("(a + b]", &result);
    assert(status == BRACKETS_OK && result == 0);
    printf("Тест 8 пройден\n");
    
    status = check_brackets(NULL, &result);
    assert(status == BRACKETS_INVALID_INPUT);
    printf("Тест 9 пройден\n");
    
    status = check_brackets("test", NULL);
    assert(status == BRACKETS_INVALID_INPUT);
    printf("Тест 10 пройден\n");
    
    printf("Все тесты пройдены успешно!\n");
}

int main() {
    run_tests();
    return 0;
}