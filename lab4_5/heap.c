#include "../include/heap.h"
#include <stdlib.h>
#include <stdio.h>

static size_t parent_index(size_t i) { return (i - 1) / 2; }
static size_t left_child(size_t i) { return 2 * i + 1; }
static size_t right_child(size_t i) { return 2 * i + 2; }

static void heapify_up(Heap *heap, size_t index) {
    while (index > 0) {
        size_t parent = parent_index(index);
        if (heap->data[parent] <= heap->data[index]) break;
        
        int temp = heap->data[index];
        heap->data[index] = heap->data[parent];
        heap->data[parent] = temp;
        
        index = parent;
    }
}

static void heapify_down(Heap *heap, size_t index) {
    while (1) {
        size_t left = left_child(index);
        size_t right = right_child(index);
        size_t smallest = index;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest == index) break;

        int temp = heap->data[index];
        heap->data[index] = heap->data[smallest];
        heap->data[smallest] = temp;
        
        index = smallest;
    }
}

HeapStatus heap_create(Heap *heap, size_t capacity) {
    if (heap == NULL) {
        return HEAP_ERROR_NULL_PTR;
    }
    if (capacity == 0) {
        return HEAP_ERROR_INVALID_CAPACITY;
    }

    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;

    heap->data = (int*)calloc(capacity, sizeof(int));
    if (heap->data == NULL) {
        return HEAP_ERROR_MEMORY;
    }

    heap->capacity = capacity;
    return HEAP_SUCCESS;
}

HeapStatus heap_destroy(Heap *heap) {
    if (heap == NULL) {
        return HEAP_ERROR_NULL_PTR;
    }
    
    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
    
    return HEAP_SUCCESS;
}

HeapStatus heap_push(Heap *heap, int value) {
    if (heap == NULL) {
        return HEAP_ERROR_NULL_PTR;
    }

    if (heap->size >= heap->capacity) {
        size_t new_capacity = heap->capacity * 2;
        int *new_data = (int*)realloc(heap->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return HEAP_ERROR_MEMORY;
        }
        
        heap->data = new_data;
        heap->capacity = new_capacity;
    }

    heap->data[heap->size] = value;
    heap->size++;
    heapify_up(heap, heap->size - 1);
    
    return HEAP_SUCCESS;
}

HeapStatus heap_pop(Heap *heap, int *result) {
    if (heap == NULL || result == NULL) {
        return HEAP_ERROR_NULL_PTR;
    }
    if (heap->size == 0) {
        return HEAP_ERROR_EMPTY;
    }

    *result = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    if (heap->size > 0) {
        heapify_down(heap, 0);
    }

    return HEAP_SUCCESS;
}

HeapStatus heap_peek(const Heap *heap, int *result) {
    if (heap == NULL || result == NULL) {
        return HEAP_ERROR_NULL_PTR;
    }
    if (heap->size == 0) {
        return HEAP_ERROR_EMPTY;
    }
    
    *result = heap->data[0];
    return HEAP_SUCCESS;
}

HeapStatus heap_is_empty(const Heap *heap, int *result) {
    if (heap == NULL || result == NULL) {
        return HEAP_ERROR_NULL_PTR;
    }
    
    *result = (heap->size == 0);
    return HEAP_SUCCESS;
}

HeapStatus heap_size(const Heap *heap, size_t *result) {
    if (heap == NULL || result == NULL) {
        return HEAP_ERROR_NULL_PTR;
    }
    
    *result = heap->size;
    return HEAP_SUCCESS;
}

Heap build_heap(const int *array, size_t n) {
    Heap heap;
    if (n == 0) {
        heap_create(&heap, 1);
        return heap;
    }

    heap_create(&heap, n);
    if (heap.data == NULL) {
        return heap;
    }

    for (size_t i = 0; i < n; i++) {
        heap.data[i] = array[i];
    }
    heap.size = n;

    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify_down(&heap, i);
    }

    return heap;
}

int is_equal_heap(const Heap *h1, const Heap *h2) {
    if (h1 == NULL || h2 == NULL) {
        return 0;
    }
    if (h1->size != h2->size) {
        return 0;
    }

    for (size_t i = 0; i < h1->size; i++) {
        if (h1->data[i] != h2->data[i]) {
            return 0;
        }
    }
    return 1;
}
