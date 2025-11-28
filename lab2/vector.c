#include "vector.h"
#include <stdlib.h>
#include <string.h>

VectorStatus create_vector(size_t initial_capacity,
                          VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE),
                          void (*DeleteFunc)(VECTOR_TYPE),
                          int (*CompareFunc)(VECTOR_TYPE, VECTOR_TYPE),
                          Vector *result) {
    if (result == NULL || CopyFunc == NULL || DeleteFunc == NULL || CompareFunc == NULL) {
        return VECTOR_ERROR_NULL_PTR;
    }
    if (initial_capacity <= 0) {
        return VECTOR_ERROR_INVALID_CAPACITY;
    }

    result->size = 0;
    result->capacity = initial_capacity;
    result->CopyFunc = CopyFunc;
    result->DeleteFunc = DeleteFunc;
    result->CompareFunc = CompareFunc;

    result->data = (VECTOR_TYPE*)malloc(initial_capacity * sizeof(VECTOR_TYPE));
    if (result->data == NULL) {
        result->capacity = 0;
        result->CopyFunc = NULL;
        result->DeleteFunc = NULL;
        result->CompareFunc = NULL;
        return VECTOR_ERROR_MEMORY;
    }
    
    return VECTOR_SUCCESS;
}

VectorStatus push_back_vector(Vector* v, VECTOR_TYPE value) {
    if (v == NULL) {
        return VECTOR_ERROR_NULL_PTR;
    }

    if (v->size >= v->capacity) {
        size_t new_capacity = v->capacity * 2;
        VECTOR_TYPE *new_data = (VECTOR_TYPE*)realloc(v->data, new_capacity * sizeof(VECTOR_TYPE));
        if (new_data == NULL) {
            return VECTOR_ERROR_MEMORY;
        }
        v->data = new_data;
        v->capacity = new_capacity;
    }

    v->data[v->size] = v->CopyFunc(value);
    v->size++;
    return VECTOR_SUCCESS;
}

VectorStatus get_at_vector(const Vector *v, size_t index, VECTOR_TYPE *result) {
    if (v == NULL || result == NULL) {
        return VECTOR_ERROR_NULL_PTR;
    }
    if (index >= v->size) {
        return VECTOR_ERROR_INDEX;
    }
    *result = v->CopyFunc(v->data[index]);
    return VECTOR_SUCCESS;
}

VectorStatus delete_at_vector(Vector *v, size_t index) {
    if (v == NULL) {
        return VECTOR_ERROR_NULL_PTR;
    }
    if (index >= v->size) {
        return VECTOR_ERROR_INDEX;
    }

    v->DeleteFunc(v->data[index]);
    
    for (size_t i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }
    
    v->size--;
    
    return VECTOR_SUCCESS;
}

VectorStatus erase_vector(Vector *v) {
    if (v == NULL) {
        return VECTOR_ERROR_NULL_PTR;
    }
    while(v->size != 0) {
        v->DeleteFunc(v->data[v->size - 1]);
        v->size--;
    }
    free(v->data);
    v->data = NULL;
    v->capacity = 0;
    return VECTOR_SUCCESS;
}

VectorStatus delete_vector(Vector *v) {
    if (v == NULL) {
        return VECTOR_ERROR_NULL_PTR;
    }
    erase_vector(v);
    v->CopyFunc = NULL;
    v->DeleteFunc = NULL;
    v->CompareFunc = NULL;
    return VECTOR_SUCCESS;
}

int is_equal_vector(const Vector *v1, const Vector *v2) {
    if (v1 == v2) return 1;
    if (v1 == NULL || v2 == NULL) return 0;
    if (v1->CompareFunc == NULL) return 0;
    
    if (v1->size != v2->size) return 0;
    
    for (size_t i = 0; i < v1->size; i++) {
        if (!v1->CompareFunc(v1->data[i], v2->data[i])) {
            return 0;
        }
    }
    return 1;
}

VectorStatus copy_vector(Vector *dest, const Vector *src) {
    if (dest == NULL || src == NULL) {
        return VECTOR_ERROR_NULL_PTR;
    }
    
    VectorStatus status = erase_vector(dest);
    if (status != VECTOR_SUCCESS) {
        return status;
    }
    
    dest->CopyFunc = src->CopyFunc;
    dest->DeleteFunc = src->DeleteFunc;
    dest->CompareFunc = src->CompareFunc;
    
    dest->data = (VECTOR_TYPE*)malloc(src->capacity * sizeof(VECTOR_TYPE));
    if (dest->data == NULL) {
        return VECTOR_ERROR_MEMORY;
    }
    
    dest->capacity = src->capacity;
    dest->size = src->size;
    
    for (size_t i = 0; i < src->size; i++) {
        dest->data[i] = src->CopyFunc(src->data[i]);
    }
    
    return VECTOR_SUCCESS;
}

Vector* copy_vector_new(const Vector *src) {
    if (src == NULL) return NULL;
    
    Vector* new_vec = (Vector*)malloc(sizeof(Vector));
    if (new_vec == NULL) return NULL;
    
    if (copy_vector(new_vec, src) != VECTOR_SUCCESS) {
        free(new_vec);
        return NULL;
    }
    
    return new_vec;
}