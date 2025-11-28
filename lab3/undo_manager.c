#include "undo_manager.h"
#include <stdlib.h>

void init_undo_manager(UndoManager* manager) {
    if (manager == NULL) return;
    create_list(&manager->undo_stack);
    create_list(&manager->redo_stack);
    manager->modification_count = 0;
}

void destroy_undo_manager(UndoManager* manager) {
    if (manager == NULL) return;
    
    if (manager->undo_stack) {
        Node* current = manager->undo_stack->head;
        while (current != NULL) {
            Action* action = (Action*)current->data;
            if (action->liver_before) destroy_liver(action->liver_before);
            if (action->liver_after) destroy_liver(action->liver_after);
            free(action);
            current = current->next;
        }
        delete_list(manager->undo_stack);
    }
    
    if (manager->redo_stack) {
        Node* current = manager->redo_stack->head;
        while (current != NULL) {
            Action* action = (Action*)current->data;
            if (action->liver_before) destroy_liver(action->liver_before);
            if (action->liver_after) destroy_liver(action->liver_after);
            free(action);
            current = current->next;
        }
        delete_list(manager->redo_stack);
    }
}

void record_action(UndoManager* manager, ActionType type, Liver* liver_before, Liver* liver_after, size_t index) {
    if (manager == NULL) return;
    
    Action* action = (Action*)malloc(sizeof(Action));
    if (action == NULL) return;
    
    action->type = type;
    action->index = index;
    
    if (liver_before) {
        copy_liver(liver_before, &action->liver_before);
    } else {
        action->liver_before = NULL;
    }
    
    if (liver_after) {
        copy_liver(liver_after, &action->liver_after);
    } else {
        action->liver_after = NULL;
    }
    
    push_stack(manager->undo_stack, action);
    manager->modification_count++;
    
    if (manager->redo_stack) {
        erase_list(manager->redo_stack);
    }
}

int undo_last_actions(UndoManager* manager, LinkedList* liver_list) {
    if (manager == NULL || liver_list == NULL || manager->undo_stack == NULL) return 0;
    
    size_t undo_count = manager->modification_count / 2;
    if (undo_count == 0) return 0;
    
    size_t successful_undos = 0;
    
    for (size_t i = 0; i < undo_count && !is_list_empty(manager->undo_stack); i++) {
        Action* action = (Action*)pop_stack(manager->undo_stack);
        if (action == NULL) continue;
        
        switch (action->type) {
            case ACTION_ADD:
                if (action->liver_after) {
                    Liver* temp;
                    delete_at_list(liver_list, action->index, (LIST_TYPE*)&temp);
                }
                break;
                
            case ACTION_DELETE:
                if (action->liver_before) {
                    insert_at_list(liver_list, action->index, action->liver_before);
                }
                break;
                
            case ACTION_MODIFY:
                if (action->liver_before && action->liver_after) {
                    Liver* current_liver;
                    if (get_at_list(liver_list, action->index, (LIST_TYPE*)&current_liver) == LIST_SUCCESS) {
                        if (current_liver) {
                            destroy_liver(current_liver);
                            Liver* restored_liver;
                            if (copy_liver(action->liver_before, &restored_liver) == LIVER_SUCCESS) {
                                LIST_TYPE temp;
                                delete_at_list(liver_list, action->index, &temp);
                                insert_at_list(liver_list, action->index, restored_liver);
                            }
                        }
                    }
                }
                break;
        }
        
        if (manager->redo_stack) {
            push_stack(manager->redo_stack, action);
        } else {
            if (action->liver_before) destroy_liver(action->liver_before);
            if (action->liver_after) destroy_liver(action->liver_after);
            free(action);
        }
        
        successful_undos++;
        if (manager->modification_count > 0) manager->modification_count--;
    }
    
    return successful_undos;
}
