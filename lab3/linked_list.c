#include "linked_list.h"
#include <stdlib.h>

ListStatus create_list(LinkedList** list){
    if (list == NULL){
        return LIST_ERROR_NULL_POINTER;
    }

    *list = (LinkedList*)malloc(sizeof(LinkedList));

    if (*list == NULL){
        return LIST_ERROR_MEMORY_ALLOCATION;
    }

    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->size = 0;

    return LIST_SUCCESS;
}

ListStatus erase_list(LinkedList* list){
    if (list == NULL){
        return LIST_ERROR_NULL_POINTER;
    }

    Node* current = list->head;
    while (current != NULL){
        Node* next = current->next;
        free(current);
        current = next;
    }
    

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return LIST_SUCCESS;
}

ListStatus push_back_list(LinkedList* list, LIST_TYPE value){
    if (list == NULL){
        return LIST_ERROR_NULL_POINTER;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL){
        return LIST_ERROR_MEMORY_ALLOCATION;
    }

    new_node->data = value;
    new_node->next = NULL;

    if (list->head == NULL){
        new_node->prev = NULL;
        list->head = new_node;
        list->tail = new_node;
    }else{
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->size++;

    return LIST_SUCCESS;
}

ListStatus get_at_list(LinkedList* list, size_t index, LIST_TYPE* result){
    if (list == NULL || result == NULL){
        return LIST_ERROR_NULL_POINTER;
    }
    if (index >= list->size){
        return LIST_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    Node* current = list->head;
    for(size_t i = 0; i < index; i++){
        if (current == NULL){
            return LIST_ERROR_INDEX_OUT_OF_BOUNDS;
        }
        current = current->next;
    }
    
    if (current == NULL){
        return LIST_ERROR_INDEX_OUT_OF_BOUNDS;
    }
    
    *result = current->data;

    return LIST_SUCCESS;
}

ListStatus push_front_list(LinkedList* list, LIST_TYPE value){
    if (list == NULL){
        return LIST_ERROR_NULL_POINTER;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL){
        return LIST_ERROR_MEMORY_ALLOCATION;
    }

    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = list->head;

    if (list->head != NULL){
        list->head->prev = new_node;
    }else{
        list->tail = new_node;
    }

    list->head = new_node;

    list->size++;

    return LIST_SUCCESS;
}

ListStatus pop_front_list(LinkedList* list, LIST_TYPE* result){
    if (list == NULL || result == NULL){
        return LIST_ERROR_NULL_POINTER;
    }

    if (list->head == NULL) {
        return LIST_ERROR_EMPTY_LIST;
    }

    Node* temp = list->head;
    *result = temp->data;
    
    list->head = list->head->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }

    free(temp);
    list->size--;

    return LIST_SUCCESS;
}

size_t get_list_size(const LinkedList* list) {
    return list == NULL ? 0 : list->size;
}

int is_list_empty(const LinkedList* list) {
    return list == NULL || list->head == NULL;
}

ListStatus pop_back_list(LinkedList* list, LIST_TYPE* result) {
    if (list == NULL || result == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }
    if (list->tail == NULL) {
        return LIST_ERROR_EMPTY_LIST;
    }

    Node* temp = list->tail;
    *result = temp->data;

    list->tail = temp->prev;
    
    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }

    free(temp);
    list->size--;
    return LIST_SUCCESS;
}

ListStatus delete_at_list(LinkedList* list, size_t index, LIST_TYPE* result) {
    if (list == NULL || result == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }
    if (index >= list->size) {
        return LIST_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    Node* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    *result = current->data;

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        list->head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        list->tail = current->prev;
    }

    free(current);
    list->size--;
    return LIST_SUCCESS;
}

ListStatus delete_list(LinkedList* list){
    if (list == NULL){
        return LIST_ERROR_NULL_POINTER;
    }
    
    erase_list(list);
    free(list);
    
    return LIST_SUCCESS;
}

ListStatus insert_at_list(LinkedList* list, size_t index, LIST_TYPE value) {
    if (list == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }
    if (index > list->size) {
        return LIST_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    if (index == 0) {
        return push_front_list(list, value);
    }
    if (index == list->size) {
        return push_back_list(list, value);
    }

    Node* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return LIST_ERROR_MEMORY_ALLOCATION;
    }

    new_node->data = value;
    new_node->prev = current->prev;
    new_node->next = current;

    current->prev->next = new_node;
    current->prev = new_node;

    list->size++;
    return LIST_SUCCESS;
}

int is_equal_list(const LinkedList* list1, const LinkedList* list2) {
    if (list1 == NULL && list2 == NULL) return 1;
    if (list1 == NULL || list2 == NULL) return 0;
    if (list1->size != list2->size) return 0;
    
    Node* current1 = list1->head;
    Node* current2 = list2->head;
    
    while (current1 != NULL && current2 != NULL) {
        if (current1->data != current2->data) {
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    
    return 1;
}
