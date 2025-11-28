#include "../include/letter.h"
#include <stdlib.h>
#include <string.h>

LetterArray letter_array_create(size_t capacity) {
    LetterArray array;
    array.letters = NULL;
    array.size = 0;
    array.capacity = 0;
    
    if (capacity > 0) {
        array.letters = (Letter*)calloc(capacity, sizeof(Letter));
        if (array.letters != NULL) {
            array.capacity = capacity;
        }
    }
    
    return array;
}

void letter_array_destroy(LetterArray *array) {
    if (array != NULL) {
        free(array->letters);
        array->letters = NULL;
        array->size = 0;
        array->capacity = 0;
    }
}

int letter_array_add(LetterArray *array, const Letter *letter) {
    if (array == NULL || letter == NULL) {
        return 0;
    }
    
    if (array->size >= array->capacity) {
        size_t new_capacity = array->capacity * 2;
        if (new_capacity == 0) new_capacity = 10;
        
        Letter *new_letters = (Letter*)realloc(array->letters, new_capacity * sizeof(Letter));
        if (new_letters == NULL) {
            return 0;
        }
        
        array->letters = new_letters;
        array->capacity = new_capacity;
    }
    
    array->letters[array->size] = *letter;
    array->size++;
    return 1;
}

Letter* letter_array_get(LetterArray *array, int id) {
    if (array == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < array->size; i++) {
        if (array->letters[i].id == id) {
            return &array->letters[i];
        }
    }
    
    return NULL;
}
