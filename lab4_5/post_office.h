#ifndef POST_OFFICE_H
#define POST_OFFICE_H

#include "heap.h"
#include "letter.h"

typedef struct PostOffice {
    int id;
    int capacity;
    Heap letters_heap;
    int *connected_offices;
    size_t connected_count;
    size_t connected_capacity;
} PostOffice;

typedef struct {
    PostOffice *offices;
    size_t size;
    size_t capacity;
} PostOfficeArray;

PostOfficeArray post_office_array_create(size_t capacity);
void post_office_array_destroy(PostOfficeArray *array);
int post_office_array_add(PostOfficeArray *array, const PostOffice *office);
PostOffice* post_office_array_get(PostOfficeArray *array, int id);
int post_office_add_connection(PostOffice *office, int connected_id);
int post_office_add_letter(PostOffice *office, const Letter *letter);

#endif
