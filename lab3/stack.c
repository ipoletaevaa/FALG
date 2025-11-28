#include "linked_list.h"

void push_stack(LinkedList* stack, LIST_TYPE value) {
    push_front_list(stack, value);
}

LIST_TYPE pop_stack(LinkedList* stack) {
    LIST_TYPE result;
    pop_front_list(stack, &result);
    return result;
}

LIST_TYPE peek_stack(const LinkedList* stack) {
    return stack != NULL && stack->head != NULL ? stack->head->data : NULL;
}
