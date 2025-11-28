#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Heap;

typedef enum {
    HEAP_SUCCESS = 0,
    HEAP_ERROR_NULL_PTR = 1,
    HEAP_ERROR_MEMORY = 2,
    HEAP_ERROR_EMPTY = 3,
    HEAP_ERROR_INVALID_CAPACITY = 4
} HeapStatus;

HeapStatus heap_create(Heap *heap, size_t capacity);
HeapStatus heap_destroy(Heap *heap);
HeapStatus heap_push(Heap *heap, int value);
HeapStatus heap_pop(Heap *heap, int *result);
HeapStatus heap_peek(const Heap *heap, int *result);
HeapStatus heap_is_empty(const Heap *heap, int *result);
HeapStatus heap_size(const Heap *heap, size_t *result);
Heap build_heap(const int *array, size_t n);
int is_equal_heap(const Heap *h1, const Heap *h2);

#endif