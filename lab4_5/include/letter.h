#ifndef LETTER_H
#define LETTER_H

#include "heap.h"

typedef enum {
    LETTER_REGULAR = 0,
    LETTER_URGENT = 1
} LetterType;

typedef enum {
    LETTER_IN_TRANSIT = 0,
    LETTER_DELIVERED = 1,
    LETTER_UNDELIVERED = 2
} LetterState;

typedef struct {
    int id;
    LetterType type;
    LetterState state;
    int priority;
    int from_office;
    int to_office;
    char technical_data[256];
} Letter;

typedef struct {
    Letter *letters;
    size_t size;
    size_t capacity;
} LetterArray;

LetterArray letter_array_create(size_t capacity);
void letter_array_destroy(LetterArray *array);
int letter_array_add(LetterArray *array, const Letter *letter);
Letter* letter_array_get(LetterArray *array, int id);

#endif