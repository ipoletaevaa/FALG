#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "liver.h"
#include "undo_manager.h"

void print_menu() {
    printf("\n=== СИСТЕМА УПРАВЛЕНИЯ ЖИТЕЛЯМИ ===\n");
    printf("1. Загрузить данные из файла\n");
    printf("2. Сохранить данные в файл\n");
    printf("3. Показать всех жителей\n");
    printf("4. Найти жителя по ID\n");
    printf("5. Найти жителей по имени\n");
    printf("6. Фильтровать по возрасту\n");
    printf("7. Фильтровать по доходу\n");
    printf("8. Добавить жителя\n");
    printf("9. Удалить жителя\n");
    printf("10. Отменить последние изменения (Undo)\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
}

void display_livers(const LinkedList* list) {
    if (list == NULL || is_list_empty(list)) {
        printf("Список пуст.\n");
        return;
    }
    printf("\n=== СПИСОК ЖИТЕЛЕЙ ===\n");
    Node* current = list->head;
    size_t count = 0;
    while (current != NULL) {
        printf("%zu. ", ++count);
        print_liver((Liver*)current->data);
        current = current->next;
    }
    printf("Всего: %zu жителей\n", count);
}

void add_liver_interactive(LinkedList* list, UndoManager* undo_manager) {
    printf("\n=== ДОБАВЛЕНИЕ НОВОГО ЖИТЕЛЯ ===\n");
    unsigned int id;
    char surname[100], name[100], patronymic[100];
    Date birth_date;
    char gender;
    double income;
    
    printf("ID: "); scanf("%u", &id);
    printf("Фамилия: "); scanf("%99s", surname);
    printf("Имя: "); scanf("%99s", name);
    printf("Отчество: "); scanf("%99s", patronymic);
    printf("Дата рождения (день месяц год): "); 
    scanf("%d %d %d", &birth_date.day, &birth_date.month, &birth_date.year);
    printf("Пол (M/W): "); scanf(" %c", &gender);
    printf("Средний доход: "); scanf("%lf", &income);
    
    if (!is_valid_name(surname) || !is_valid_name(name) || 
        !is_valid_date(&birth_date) || !is_valid_gender(gender) ||
        !is_valid_income(income)) {
        printf("Ошибка: неверные данные!\n");
        return;
    }
    
    if (find_liver_by_id(list, id) != NULL) {
        printf("Ошибка: житель с ID %u уже существует!\n", id);
        return;
    }
    
    Liver* new_liver = create_liver(id, surname, name, patronymic, birth_date, gender, income);
    if (new_liver == NULL) {
        printf("Ошибка создания жителя!\n");
        return;
    }
    
    Node* current = list->head;
    size_t index = 0;
    while (current != NULL) {
        Liver* current_liver = (Liver*)current->data;
        if (compare_liver_by_age(new_liver, current_liver) >= 0) {
            break;
        }
        current = current->next;
        index++;
    }
    
    if (insert_at_list(list, index, new_liver) == LIST_SUCCESS) {
        if (undo_manager) {
            record_action(undo_manager, ACTION_ADD, NULL, new_liver, index);
        }
        printf("Житель успешно добавлен!\n");
    } else {
        destroy_liver(new_liver);
        printf("Ошибка добавления жителя!\n");
    }
}

void delete_liver_interactive(LinkedList* list, UndoManager* undo_manager) {
    if (list == NULL || is_list_empty(list)) {
        printf("Список пуст!\n");
        return;
    }
    
    unsigned int id;
    printf("Введите ID жителя для удаления: ");
    scanf("%u", &id);
    
    Node* current = list->head;
    size_t index = 0;
    Liver* liver_to_delete = NULL;
    
    while (current != NULL) {
        Liver* liver = (Liver*)current->data;
        if (liver->id == id) {
            liver_to_delete = liver;
            break;
        }
        current = current->next;
        index++;
    }
    
    if (liver_to_delete == NULL) {
        printf("Житель с ID %u не найден.\n", id);
        return;
    }
    
    Liver* liver_copy;
    if (copy_liver(liver_to_delete, &liver_copy) == LIVER_SUCCESS) {
        LIST_TYPE result;
        if (delete_at_list(list, index, &result) == LIST_SUCCESS) {
            if (undo_manager) {
                record_action(undo_manager, ACTION_DELETE, liver_copy, NULL, index);
            } else {
                destroy_liver(liver_copy);
            }
            printf("Житель успешно удален!\n");
        } else {
            destroy_liver(liver_copy);
            printf("Ошибка удаления жителя!\n");
        }
    } else {
        printf("Ошибка копирования данных жителя!\n");
    }
}

int main() {
    LinkedList* liver_list = NULL;
    UndoManager undo_manager;
    char filename[256];
    int choice;
    
    init_undo_manager(&undo_manager);
    
    do {
        print_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                printf("Введите путь к файлу: ");
                scanf("%255s", filename);
                LiverStatus status = load_livers_from_file(filename, &liver_list);
                if (status == LIVER_SUCCESS) {
                    printf("Данные успешно загружены!\n");
                } else {
                    printf("Ошибка загрузки файла!\n");
                }
                break;
            }
            
            case 2: {
                if (liver_list == NULL) {
                    printf("Список пуст!\n");
                    break;
                }
                printf("Введите путь для сохранения: ");
                scanf("%255s", filename);
                LiverStatus status = save_livers_to_file(filename, liver_list);
                if (status == LIVER_SUCCESS) {
                    printf("Данные успешно сохранены!\n");
                } else {
                    printf("Ошибка сохранения файла!\n");
                }
                break;
            }
            
            case 3:
                display_livers(liver_list);
                break;
                
            case 4: {
                unsigned int id;
                printf("Введите ID: ");
                scanf("%u", &id);
                Liver* liver = find_liver_by_id(liver_list, id);
                if (liver) {
                    printf("Найден житель: ");
                    print_liver(liver);
                } else {
                    printf("Житель с ID %u не найден.\n", id);
                }
                break;
            }
            
            case 5: {
                char name[100];
                printf("Введите имя или фамилию: ");
                scanf("%99s", name);
                LinkedList* result = find_livers_by_name(liver_list, name);
                if (result && !is_list_empty(result)) {
                    display_livers(result);
                } else {
                    printf("Жители с именем/фамилией '%s' не найдены.\n", name);
                }
                if (result) delete_list(result);
                break;
            }
            
            case 6: {
                int min_age, max_age;
                printf("Введите минимальный возраст: ");
                scanf("%d", &min_age);
                printf("Введите максимальный возраст: ");
                scanf("%d", &max_age);
                LinkedList* result = filter_livers_by_age(liver_list, min_age, max_age);
                if (result && !is_list_empty(result)) {
                    display_livers(result);
                } else {
                    printf("Жители в возрасте от %d до %d лет не найдены.\n", min_age, max_age);
                }
                if (result) delete_list(result);
                break;
            }
            
            case 7: {
                double min_income, max_income;
                printf("Введите минимальный доход: ");
                scanf("%lf", &min_income);
                printf("Введите максимальный доход: ");
                scanf("%lf", &max_income);
                LinkedList* result = filter_livers_by_income(liver_list, min_income, max_income);
                if (result && !is_list_empty(result)) {
                    display_livers(result);
                } else {
                    printf("Жители с доходом от %.2f до %.2f не найдены.\n", min_income, max_income);
                }
                if (result) delete_list(result);
                break;
            }
            
            case 8:
                if (liver_list == NULL) {
                    create_list(&liver_list);
                }
                add_liver_interactive(liver_list, &undo_manager);
                break;
                
            case 9:
                if (liver_list == NULL) {
                    printf("Список пуст!\n");
                } else {
                    delete_liver_interactive(liver_list, &undo_manager);
                }
                break;
                
            case 10: {
                int undone = undo_last_actions(&undo_manager, liver_list);
                if (undone > 0) {
                    printf("Отменено %d последних изменений\n", undone);
                } else {
                    printf("Нет изменений для отмены\n");
                }
                break;
            }
                
            case 0:
                printf("Выход из программы.\n");
                break;
                
            default:
                printf("Неверный выбор!\n");
        }
    } while (choice != 0);
    
    if (liver_list) {
        Node* current = liver_list->head;
        while (current != NULL) {
            destroy_liver((Liver*)current->data);
            current = current->next;
        }
        delete_list(liver_list);
    }
    
    destroy_undo_manager(&undo_manager);
    
    return 0;
}
