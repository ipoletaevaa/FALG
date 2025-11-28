#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"

void enqueue(LinkedList* queue, LIST_TYPE value);
LIST_TYPE dequeue(LinkedList* queue);
LIST_TYPE peek_queue(const LinkedList* queue);

#endif
