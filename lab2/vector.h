#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#ifndef VECTOR_TYPE
#error "VECTOR_TYPE must be defined before including vector.h"
#endif

typedef struct {
    VECTOR_TYPE *data;
    size_t size;
    size_t capacity;
    VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE);
    void (*DeleteFunc)(VECTOR_TYPE);
    int (*CompareFunc)(VECTOR_TYPE, VECTOR_TYPE);
} Vector;

typedef enum {
    VECTOR_SUCCESS,
    VECTOR_ERROR_NULL_PTR,
    VECTOR_ERROR_MEMORY,
    VECTOR_ERROR_INDEX,
    VECTOR_ERROR_EMPTY,
    VECTOR_ERROR_INVALID_CAPACITY,
    VECTOR_ERROR_INVALID_DATA
} VectorStatus;

VectorStatus create_vector(size_t initial_capacity,
                          VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE),
                          void (*DeleteFunc)(VECTOR_TYPE),
                          int (*CompareFunc)(VECTOR_TYPE, VECTOR_TYPE),
                          Vector *result);

VectorStatus push_back_vector(Vector *v, VECTOR_TYPE value);
VectorStatus get_at_vector(const Vector *v, size_t index, VECTOR_TYPE *result);
VectorStatus delete_at_vector(Vector *v, size_t index);
VectorStatus erase_vector(Vector *v);
VectorStatus delete_vector(Vector *v);
int is_equal_vector(const Vector *v1, const Vector *v2);
VectorStatus copy_vector(Vector *dest, const Vector *src);
Vector* copy_vector_new(const Vector *src);

#endif