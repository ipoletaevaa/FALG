#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_TYPE char*
#include "vector.h"

char* copy_string(char* str) {
    return strdup(str);
}

void delete_string(char* str) {
    free(str);
}

int compare_string(char* a, char* b) {
    if (a == NULL && b == NULL) return 1;
    if (a == NULL || b == NULL) return 0;
    return strcmp(a, b) == 0;
}

void test_string_vector() {
    printf("=== Тестирование вектора для строк ===\n");
    
    Vector vec;
    create_vector(2, copy_string, delete_string, compare_string, &vec);
    
    push_back_vector(&vec, "Привет");
    push_back_vector(&vec, "Мир");
    push_back_vector(&vec, "Тест");
    
    char* value;
    for (size_t i = 0; i < vec.size; i++) {
        get_at_vector(&vec, i, &value);
        printf("Элемент на позиции %zu: %s\n", i, value);
        free(value);
    }
    
    delete_vector(&vec);
    printf("Вектор строк удалён\n\n");
}

int main() {
    printf("=== Начало тестирования библиотеки Vector ===\n\n");
    test_string_vector();
    printf("=== Все тесты завершены успешно! ===\n");
    return 0;
}