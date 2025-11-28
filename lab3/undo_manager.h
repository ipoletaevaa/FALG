#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H

#include "linked_list.h"
#include "liver.h"

typedef enum {
    ACTION_ADD,
    ACTION_DELETE,
    ACTION_MODIFY
} ActionType;

typedef struct {
    ActionType type;
    Liver* liver_before;
    Liver* liver_after;
    size_t index;
} Action;

typedef struct {
    LinkedList* undo_stack;
    LinkedList* redo_stack;
    size_t modification_count;
} UndoManager;

void init_undo_manager(UndoManager* manager);
void destroy_undo_manager(UndoManager* manager);
void record_action(UndoManager* manager, ActionType type, Liver* liver_before, Liver* liver_after, size_t index);
int undo_last_actions(UndoManager* manager, LinkedList* liver_list);

#endif
