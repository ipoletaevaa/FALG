#ifndef STACK_H
#define STACK_H

#include "linked_list.h"

void push_stack(LinkedList* stack, LIST_TYPE value);
LIST_TYPE pop_stack(LinkedList* stack);
LIST_TYPE peek_stack(const LinkedList* stack);

#endif
