#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_TYPE int
#include "vector.h"

int copy_int(int value) {
    return value;
}

void delete_int(int value) {
    (void)value;
}

int compare_int(int a, int b) {
    return a - b;
}

int main() {
    printf("=== Тестирование вектора для int ===\n");
    
    Vector vec;
    VectorStatus status;
    
    status = create_vector(2, copy_int, delete_int, compare_int, &vec);
    if (status != VECTOR_SUCCESS) {
        printf("Ошибка создания: %d\n", status);
        return 1;
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
    printf("Векторы удалены\n");
    printf("=== Тесты завершены успешно! ===\n");
    return 0;
}