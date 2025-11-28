#include "linked_list.h"

void enqueue(LinkedList* queue, LIST_TYPE value) {
    push_back_list(queue, value);
}

LIST_TYPE dequeue(LinkedList* queue) {
    LIST_TYPE result;
    pop_front_list(queue, &result);
    return result;
}

LIST_TYPE peek_queue(const LinkedList* queue) {
    return queue != NULL && queue->head != NULL ? queue->head->data : NULL;
}