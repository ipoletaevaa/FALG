#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef void* LIST_TYPE;

typedef struct Node{
    LIST_TYPE data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct LinkedList{
    Node* head;
    Node* tail;
    size_t size;
} LinkedList;

typedef enum ListStatus{
    LIST_SUCCESS = 0, 
    LIST_ERROR_NULL_POINTER = 1,
    LIST_ERROR_EMPTY_LIST = 2,
    LIST_ERROR_INDEX_OUT_OF_BOUNDS = 3,
    LIST_ERROR_MEMORY_ALLOCATION = 4,
    LIST_ERROR_INVALID_DATA = 5
} ListStatus;

ListStatus create_list(LinkedList** list);
ListStatus erase_list(LinkedList* list);
ListStatus delete_list(LinkedList* list);

ListStatus push_back_list(LinkedList* list, LIST_TYPE value);
ListStatus push_front_list(LinkedList* list, LIST_TYPE value);

ListStatus pop_back_list(LinkedList* list, LIST_TYPE* result);
ListStatus pop_front_list(LinkedList* list, LIST_TYPE* result);

ListStatus insert_at_list(LinkedList* list, size_t index, LIST_TYPE value);
ListStatus delete_at_list(LinkedList* list, size_t index, LIST_TYPE* result);
ListStatus get_at_list(LinkedList* list, size_t index, LIST_TYPE* result);

size_t get_list_size(const LinkedList* list);
int is_list_empty(const LinkedList* list);
int is_equal_list(const LinkedList* list1, const LinkedList* list2);

void push_stack(LinkedList* stack, LIST_TYPE value);
LIST_TYPE pop_stack(LinkedList* stack);
LIST_TYPE peek_stack(const LinkedList* stack);
void enqueue(LinkedList* queue, LIST_TYPE value);
LIST_TYPE dequeue(LinkedList* queue);
LIST_TYPE peek_queue(const LinkedList* queue);

#endif
