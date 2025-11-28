#include "../include/heap.h"
#include <stdio.h>
#include <assert.h>

void test_heap_create_destroy() {
    Heap heap;
    HeapStatus status = heap_create(&heap, 10);
    assert(status == HEAP_SUCCESS);
    assert(heap.capacity == 10);
    assert(heap.size == 0);
    assert(heap.data != NULL);
    
    status = heap_destroy(&heap);
    assert(status == HEAP_SUCCESS);
    printf("test_heap_create_destroy: ПРОЙДЕН\n");
}

void test_heap_push_pop() {
    Heap heap;
    heap_create(&heap, 5);
    
    assert(heap_push(&heap, 5) == HEAP_SUCCESS);
    assert(heap_push(&heap, 3) == HEAP_SUCCESS);
    assert(heap_push(&heap, 7) == HEAP_SUCCESS);
    assert(heap_push(&heap, 1) == HEAP_SUCCESS);
    
    size_t size;
    heap_size(&heap, &size);
    assert(size == 4);
    
    int min_val;
    assert(heap_pop(&heap, &min_val) == HEAP_SUCCESS);
    assert(min_val == 1);
    
    assert(heap_pop(&heap, &min_val) == HEAP_SUCCESS);
    assert(min_val == 3);
    
    heap_destroy(&heap);
    printf("test_heap_push_pop: ПРОЙДЕН\n");
}

void test_heap_peek() {
    Heap heap;
    heap_create(&heap, 5);
    
    heap_push(&heap, 5);
    heap_push(&heap, 2);
    heap_push(&heap, 8);
    
    int min_val;
    assert(heap_peek(&heap, &min_val) == HEAP_SUCCESS);
    assert(min_val == 2);
    
    size_t size;
    heap_size(&heap, &size);
    assert(size == 3);
    
    heap_destroy(&heap);
    printf("test_heap_peek: ПРОЙДЕН\n");
}

void test_heap_empty() {
    Heap heap;
    heap_create(&heap, 5);
    
    int is_empty;
    assert(heap_is_empty(&heap, &is_empty) == HEAP_SUCCESS);
    assert(is_empty == 1);
    
    heap_push(&heap, 1);
    assert(heap_is_empty(&heap, &is_empty) == HEAP_SUCCESS);
    assert(is_empty == 0);
    
    heap_destroy(&heap);
    printf("test_heap_empty: ПРОЙДЕН\n");
}

void test_heap_size() {
    Heap heap;
    heap_create(&heap, 5);
    
    size_t size;
    assert(heap_size(&heap, &size) == HEAP_SUCCESS);
    assert(size == 0);
    
    heap_push(&heap, 1);
    heap_push(&heap, 2);
    
    assert(heap_size(&heap, &size) == HEAP_SUCCESS);
    assert(size == 2);
    
    heap_destroy(&heap);
    printf("test_heap_size: ПРОЙДЕН\n");
}

void test_build_heap() {
    int array[] = {5, 3, 8, 1, 2};
    Heap heap = build_heap(array, 5);
    
    int min_val;
    assert(heap_peek(&heap, &min_val) == HEAP_SUCCESS);
    assert(min_val == 1);
    
    heap_destroy(&heap);
    printf("test_build_heap: ПРОЙДЕН\n");
}

void test_is_equal_heap() {
    int array1[] = {1, 2, 3};
    int array2[] = {1, 2, 3};
    int array3[] = {1, 3, 2};
    
    Heap heap1 = build_heap(array1, 3);
    Heap heap2 = build_heap(array2, 3);
    Heap heap3 = build_heap(array3, 3);
    
    assert(is_equal_heap(&heap1, &heap2) == 1);
    assert(is_equal_heap(&heap1, &heap3) == 0);
    
    heap_destroy(&heap1);
    heap_destroy(&heap2);
    heap_destroy(&heap3);
    printf("test_is_equal_heap: ПРОЙДЕН\n");
}

void test_heap_errors() {
    Heap heap;
    int result;
    size_t size_result;
    
    assert(heap_create(NULL, 10) == HEAP_ERROR_NULL_PTR);
    assert(heap_create(&heap, 0) == HEAP_ERROR_INVALID_CAPACITY);
    
    heap_create(&heap, 5);
    assert(heap_push(NULL, 1) == HEAP_ERROR_NULL_PTR);
    assert(heap_pop(NULL, &result) == HEAP_ERROR_NULL_PTR);
    assert(heap_pop(&heap, NULL) == HEAP_ERROR_NULL_PTR);
    assert(heap_peek(&heap, NULL) == HEAP_ERROR_NULL_PTR);
    assert(heap_is_empty(NULL, &result) == HEAP_ERROR_NULL_PTR);
    assert(heap_is_empty(&heap, NULL) == HEAP_ERROR_NULL_PTR);
    assert(heap_size(NULL, &size_result) == HEAP_ERROR_NULL_PTR);
    assert(heap_size(&heap, NULL) == HEAP_ERROR_NULL_PTR);
    
    assert(heap_pop(&heap, &result) == HEAP_ERROR_EMPTY);
    assert(heap_peek(&heap, &result) == HEAP_ERROR_EMPTY);
    
    heap_destroy(&heap);
    printf("test_heap_errors: ПРОЙДЕН\n");
}

int main() {
    printf("Запуск тестов кучи...\n");
    
    test_heap_create_destroy();
    test_heap_push_pop();
    test_heap_peek();
    test_heap_empty();
    test_heap_size();
    test_build_heap();
    test_is_equal_heap();
    test_heap_errors();
    
    printf("Все тесты ПРОЙДЕНЫ!\n");
    return 0;
}