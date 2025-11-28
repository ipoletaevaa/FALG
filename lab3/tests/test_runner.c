#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/linked_list.h"
#include "../include/liver.h"
#include "../include/undo_manager.h"

void test_list_creation() {
    printf("=== Тест 1: Создание и удаление списка ===\n");
    
    LinkedList* list;
    ListStatus status = create_list(&list);
    
    assert(status == LIST_SUCCESS);
    assert(list != NULL);
    assert(get_list_size(list) == 0);
    assert(is_list_empty(list) == 1);
    
    printf("Список успешно создан\n");
    
    status = delete_list(list);
    assert(status == LIST_SUCCESS);
    printf("Список успешно удален\n\n");
}

void test_add_remove() {
    printf("=== Тест 2: Добавление и удаление элементов ===\n");
    
    LinkedList* list;
    create_list(&list);
    
    int data1 = 100, data2 = 200, data3 = 300;
    
    push_front_list(list, &data1);
    assert(get_list_size(list) == 1);
    printf("Добавлен элемент в начало\n");
    
    push_back_list(list, &data2);
    assert(get_list_size(list) == 2);
    printf("Добавлен элемент в конец\n");
    
    insert_at_list(list, 1, &data3);
    assert(get_list_size(list) == 3);
    printf("Добавлен элемент по индексу 1\n");
    
    printf("Размер списка после добавлений: %zu\n", get_list_size(list));
    
    LIST_TYPE result;
    pop_front_list(list, &result);
    assert(*(int*)result == 100);
    assert(get_list_size(list) == 2);
    printf("Удален элемент из начала: %d\n", *(int*)result);
    
    pop_back_list(list, &result);
    assert(*(int*)result == 200);
    assert(get_list_size(list) == 1);
    printf("Удален элемент с конца: %d\n", *(int*)result);
    
    printf("Размер списка после удалений: %zu\n", get_list_size(list));
    
    delete_list(list);
    printf("\n");
}

void test_stack() {
    printf("=== Тест 3: Работа со стеком ===\n");
    
    LinkedList* stack;
    create_list(&stack);
    
    int values[] = {10, 20, 30};
    
    for (int i = 0; i < 3; i++) {
        push_stack(stack, &values[i]);
        printf("Добавлен в стек: %d\n", values[i]);
    }
    
    assert(get_list_size(stack) == 3);
    
    int* value = (int*)peek_stack(stack);
    assert(*value == 30);
    printf("Верхний элемент стека: %d\n", *value);
    
    while (!is_list_empty(stack)) {
        int* value = (int*)pop_stack(stack);
        printf("Извлечен из стека: %d\n", *value);
    }
    
    assert(is_list_empty(stack));
    delete_list(stack);
    printf("\n");
}

void test_queue() {
    printf("=== Тест 4: Работа с очередью ===\n");
    
    LinkedList* queue;
    create_list(&queue);
    
    int values[] = {10, 20, 30};
    
    for (int i = 0; i < 3; i++) {
        enqueue(queue, &values[i]);
        printf("Добавлен в очередь: %d\n", values[i]);
    }
    
    assert(get_list_size(queue) == 3);
    
    int* value = (int*)peek_queue(queue);
    assert(*value == 10);
    printf("Первый элемент очереди: %d\n", *value);
    
    while (!is_list_empty(queue)) {
        int* value = (int*)dequeue(queue);
        printf("Извлечен из очереди: %d\n", *value);
    }
    
    assert(is_list_empty(queue));
    delete_list(queue);
    printf("\n");
}

void test_liver_operations() {
    printf("=== Тест 5: Операции с жителями ===\n");
    
    Date date = {15, 5, 1990};
    Liver* liver = create_liver(1, "Ivanov", "Ivan", "Ivanovich", date, 'M', 50000.0);
    
    assert(liver != NULL);
    assert(liver->id == 1);
    assert(strcmp(liver->surname, "Ivanov") == 0);
    assert(strcmp(liver->name, "Ivan") == 0);
    assert(strcmp(liver->patronymic, "Ivanovich") == 0);
    assert(liver->birth_date.day == 15);
    assert(liver->birth_date.month == 5);
    assert(liver->birth_date.year == 1990);
    assert(liver->gender == 'M');
    assert(liver->average_income == 50000.0);
    
    printf("Житель успешно создан\n");
    printf("ID: %u\n", liver->id);
    printf("Имя: %s %s %s\n", liver->surname, liver->name, liver->patronymic);
    printf("Дата рождения: %02d.%02d.%d\n", liver->birth_date.day, liver->birth_date.month, liver->birth_date.year);
    printf("Пол: %c\n", liver->gender);
    printf("Доход: %.2f\n", liver->average_income);
    
    assert(is_valid_name("Ivan") == 1);
    assert(is_valid_name("Ivan123") == 0);
    assert(is_valid_name("") == 0);
    
    assert(is_valid_date(&date) == 1);
    Date invalid_date = {32, 13, 1800};
    assert(is_valid_date(&invalid_date) == 0);
    
    assert(is_valid_gender('M') == 1);
    assert(is_valid_gender('W') == 1);
    assert(is_valid_gender('X') == 0);
    
    assert(is_valid_income(50000.0) == 1);
    assert(is_valid_income(-100.0) == 0);
    
    printf("Валидация данных работает корректно\n");
    
    destroy_liver(liver);
    printf("Житель успешно уничтожен\n\n");
}

void test_undo_system() {
    printf("=== Тест 6: Система Undo ===\n");
    
    LinkedList* liver_list;
    create_list(&liver_list);
    UndoManager undo_manager;
    init_undo_manager(&undo_manager);
    
    Date date1 = {15, 5, 1990};
    Date date2 = {20, 8, 1985};
    
    Liver* liver1 = create_liver(1, "Ivanov", "Ivan", "Ivanovich", date1, 'M', 50000.0);
    Liver* liver2 = create_liver(2, "Petrova", "Maria", "Sergeevna", date2, 'W', 60000.0);
    
    push_back_list(liver_list, liver1);
    record_action(&undo_manager, ACTION_ADD, NULL, liver1, 0);
    
    push_back_list(liver_list, liver2);
    record_action(&undo_manager, ACTION_ADD, NULL, liver2, 1);
    
    assert(get_list_size(liver_list) == 2);
    assert(undo_manager.modification_count == 2);
    
    printf("Добавлено 2 жителя\n");
    printf("Количество изменений: %zu\n", undo_manager.modification_count);
    
    LIST_TYPE temp;
    delete_at_list(liver_list, 0, &temp);
    record_action(&undo_manager, ACTION_DELETE, (Liver*)temp, NULL, 0);
    
    assert(get_list_size(liver_list) == 1);
    assert(undo_manager.modification_count == 3);
    
    printf("Удален 1 житель\n");
    printf("Количество изменений после удаления: %zu\n", undo_manager.modification_count);
    
    int undone = undo_last_actions(&undo_manager, liver_list);
    assert(undone == 1);
    assert(get_list_size(liver_list) == 2);
    assert(undo_manager.modification_count == 2);
    
    printf("Отменено действий: %d\n", undone);
    printf("Количество изменений после отмены: %zu\n", undo_manager.modification_count);
    printf("Размер списка после отмены: %zu\n", get_list_size(liver_list));
    
    Node* current = liver_list->head;
    while (current != NULL) {
        destroy_liver((Liver*)current->data);
        current = current->next;
    }
    delete_list(liver_list);
    destroy_undo_manager(&undo_manager);
    
    printf("\n");
}

void test_search_and_filter() {
    printf("=== Тест 7: Поиск и фильтрация ===\n");
    
    LinkedList* list;
    create_list(&list);
    
    Date date1 = {15, 5, 1990};
    Date date2 = {20, 8, 1985};
    Date date3 = {10, 12, 1995};
    
    Liver* liver1 = create_liver(1, "Ivanov", "Ivan", "Ivanovich", date1, 'M', 50000.0);
    Liver* liver2 = create_liver(2, "Petrova", "Maria", "Sergeevna", date2, 'W', 60000.0);
    Liver* liver3 = create_liver(3, "Ivanov", "Sergey", "Petrovich", date3, 'M', 45000.0);
    
    push_back_list(list, liver1);
    push_back_list(list, liver2);
    push_back_list(list, liver3);
    
    Liver* found = find_liver_by_id(list, 2);
    assert(found != NULL);
    assert(found->id == 2);
    assert(strcmp(found->name, "Maria") == 0);
    printf("Поиск по ID работает\n");
    
    LinkedList* name_results = find_livers_by_name(list, "Ivanov");
    assert(name_results != NULL);
    assert(get_list_size(name_results) == 2);
    printf("Поиск по имени работает (найдено: %zu)\n", get_list_size(name_results));
    delete_list(name_results);
    
    LinkedList* income_results = filter_livers_by_income(list, 40000.0, 55000.0);
    assert(income_results != NULL);
    assert(get_list_size(income_results) == 2);
    printf("Фильтрация по доходу работает (найдено: %zu)\n", get_list_size(income_results));
    delete_list(income_results);
    
    Node* current = list->head;
    while (current != NULL) {
        destroy_liver((Liver*)current->data);
        current = current->next;
    }
    delete_list(list);
    
    printf("\n");
}

void test_file_operations() {
    printf("=== Тест 8: Файловые операции ===\n");
    
    FILE* test_file = fopen("test_file.txt", "w");
    if (test_file) {
        fprintf(test_file, "1 Ivanov Ivan Ivanovich 15 5 1990 M 50000.0\n");
        fprintf(test_file, "2 Petrova Maria Sergeevna 20 8 1985 W 60000.0\n");
        fclose(test_file);
        
        LinkedList* loaded_list;
        LiverStatus status = load_livers_from_file("test_file.txt", &loaded_list);
        
        if (status == LIVER_SUCCESS && loaded_list != NULL) {
            assert(get_list_size(loaded_list) == 2);
            printf("Файл успешно загружен\n");
            printf("Загружено жителей: %zu\n", get_list_size(loaded_list));
            
            LiverStatus save_status = save_livers_to_file("test_output.txt", loaded_list);
            assert(save_status == LIVER_SUCCESS);
            printf("Файл успешно сохранен\n");
            
            Node* current = loaded_list->head;
            while (current != NULL) {
                destroy_liver((Liver*)current->data);
                current = current->next;
            }
            delete_list(loaded_list);
        } else {
            printf("Ошибка загрузки файла: %d\n", status);
        }
        
        remove("test_file.txt");
        remove("test_output.txt");
    }
    printf("\n");
}

void test_error_handling() {
    printf("=== Тест 9: Обработка ошибок ===\n");
    
    LinkedList* list = NULL;
    ListStatus status = create_list(&list);
    assert(status == LIST_SUCCESS);
    
    ListStatus push_status = push_back_list(NULL, NULL);
    assert(push_status == LIST_ERROR_NULL_POINTER);
    printf("Обработка нулевых указателей работает\n");
    
    LIST_TYPE result;
    ListStatus pop_status = pop_front_list(list, &result);
    assert(pop_status == LIST_ERROR_EMPTY_LIST);
    printf("Обработка пустого списка работает\n");
    
    ListStatus get_status = get_at_list(list, 10, &result);
    assert(get_status == LIST_ERROR_INDEX_OUT_OF_BOUNDS);
    printf("Обработка неверных индексов работает\n");
    
    delete_list(list);
    printf("\n");
}

int main() {
    printf("ЗАПУСК АВТОМАТИЧЕСКИХ ТЕСТОВ\n\n");
    
    test_list_creation();
    test_add_remove();
    test_stack();
    test_queue();
    test_liver_operations();
    test_undo_system();
    test_search_and_filter();
    test_file_operations();
    test_error_handling();
    
    printf("ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ\n");
    printf("9 тестов завершены без ошибок\n");
    
    return 0;
}