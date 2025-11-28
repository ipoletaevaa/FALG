#include "../include/post_office.h"
#include <stdlib.h>
#include <string.h>

PostOfficeArray post_office_array_create(size_t capacity) {
    PostOfficeArray array;
    array.offices = NULL;
    array.size = 0;
    array.capacity = 0;
    
    if (capacity > 0) {
        array.offices = (PostOffice*)calloc(capacity, sizeof(PostOffice));
        if (array.offices != NULL) {
            array.capacity = capacity;
        }
    }
    
    return array;
}

void post_office_array_destroy(PostOfficeArray *array) {
    if (array != NULL) {
        for (size_t i = 0; i < array->size; i++) {
            heap_destroy(&array->offices[i].letters_heap);
            free(array->offices[i].connected_offices);
        }
        free(array->offices);
        array->offices = NULL;
        array->size = 0;
        array->capacity = 0;
    }
}

int post_office_array_add(PostOfficeArray *array, const PostOffice *office) {
    if (array == NULL || office == NULL) {
        return 0;
    }
    
    if (array->size >= array->capacity) {
        size_t new_capacity = array->capacity * 2;
        if (new_capacity == 0) new_capacity = 10;
        
        PostOffice *new_offices = (PostOffice*)realloc(array->offices, new_capacity * sizeof(PostOffice));
        if (new_offices == NULL) {
            return 0;
        }
        
        array->offices = new_offices;
        array->capacity = new_capacity;
    }
    
    array->offices[array->size] = *office;
    array->size++;
    return 1;
}

PostOffice* post_office_array_get(PostOfficeArray *array, int id) {
    if (array == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < array->size; i++) {
        if (array->offices[i].id == id) {
            return &array->offices[i];
        }
    }
    
    return NULL;
}

int post_office_add_connection(PostOffice *office, int connected_id) {
    if (office == NULL) {
        return 0;
    }
    
    if (office->connected_count >= office->connected_capacity) {
        size_t new_capacity = office->connected_capacity * 2;
        if (new_capacity == 0) new_capacity = 10;
        
        int *new_connections = (int*)realloc(office->connected_offices, new_capacity * sizeof(int));
        if (new_connections == NULL) {
            return 0;
        }
        
        office->connected_offices = new_connections;
        office->connected_capacity = new_capacity;
    }
    
    office->connected_offices[office->connected_count] = connected_id;
    office->connected_count++;
    return 1;
}

int post_office_add_letter(PostOffice *office, const Letter *letter) {
    if (office == NULL || letter == NULL) {
        return 0;
    }
    
    size_t current_size;
    heap_size(&office->letters_heap, &current_size);
    
    if (current_size >= (size_t)office->capacity) {
        return 0;
    }
    
    return heap_push(&office->letters_heap, letter->priority) == HEAP_SUCCESS;
}
