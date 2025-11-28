#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_TYPE int
#include "vector.h"

int copy_int(int value) {
    return value;
}

void delete_int(int value) {
}

int compare_int(int a, int b) {
    return a == b;
}

void test_int_vector() {
    printf("=== Тестирование вектора для int ===\n");
    
    Vector vec;
    VectorStatus status;
    
    status = create_vector(2, copy_int, delete_int, compare_int, &vec);
    if (status != VECTOR_SUCCESS) {
        printf("Ошибка создания: %d\n", status);
        return;
    }
    printf("Вектор создан: размер=%zu, вместимость=%zu\n", vec.size, vec.capacity);
    
    for (int i = 1; i <= 5; i++) {
        status = push_back_vector(&vec, i * 10);
        if (status != VECTOR_SUCCESS) {
            printf("Ошибка добавления: %d\n", status);
            break;
        }
        printf("Добавлен %d: размер=%zu, вместимость=%zu\n", i*10, vec.size, vec.capacity);
    }
    
    int value;
    for (size_t i = 0; i < vec.size; i++) {
        status = get_at_vector(&vec, i, &value);
        if (status == VECTOR_SUCCESS) {
            printf("Элемент на позиции %zu: %d\n", i, value);
        }
    }
    
    status = delete_at_vector(&vec, 1);
    if (status == VECTOR_SUCCESS) {
        printf("Удалён элемент с индексом 1\n");
    }
    
    printf("После удаления - размер: %zu\n", vec.size);
    for (size_t i = 0; i < vec.size; i++) {
        status = get_at_vector(&vec, i, &value);
        if (status == VECTOR_SUCCESS) {
            printf("Элемент на позиции %zu: %d\n", i, value);
        }
    }
    
    Vector vec2;
    create_vector(3, copy_int, delete_int, compare_int, &vec2);
    push_back_vector(&vec2, 10);
    push_back_vector(&vec2, 30);
    push_back_vector(&vec2, 40);
    
    printf("Векторы идентичны: %d\n", is_equal_vector(&vec, &vec2));
    
    Vector* copied_vec = copy_vector_new(&vec);
    if (copied_vec) {
        printf("Размер скопированного вектора: %zu\n", copied_vec->size);
        delete_vector(copied_vec);
        free(copied_vec);
    }
    
    delete_vector(&vec);
    delete_vector(&vec2);
    printf("Векторы удалены\n\n");
}

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

void test_errors() {
    printf("=== Тестирование обработки ошибок ===\n");
    
    Vector vec;
    VectorStatus status;
    
    status = create_vector(0, copy_int, delete_int, compare_int, &vec);
    printf("Создание с нулевой вместимостью: %d (ожидалось: %d)\n", 
           status, VECTOR_ERROR_INVALID_CAPACITY);
    
    status = push_back_vector(NULL, 42);
    printf("Добавление в NULL вектор: %d (ожидалось: %d)\n", 
           status, VECTOR_ERROR_NULL_PTR);
    
    status = get_at_vector(NULL, 0, NULL);
    printf("Получение из NULL вектора: %d (ожидалось: %d)\n", 
           status, VECTOR_ERROR_NULL_PTR);
    
    printf("Тестирование ошибок завершено\n\n");
}

int main() {
    printf("=== Начало тестирования библиотеки Vector ===\n\n");
    
    test_int_vector();
    test_string_vector();
    test_errors();
    
    printf("=== Все тесты завершены успешно! ===\n");
    return 0;
}