#include "include/simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_menu() {
    printf("\n=== Симуляция Почтовой Системы ===\n");
    printf("1. Добавить почтовое отделение\n");
    printf("2. Удалить почтовое отделение\n");
    printf("3. Добавить письмо\n");
    printf("4. Пометить письмо как недоставленное\n");
    printf("5. Попытка взять письмо\n");
    printf("6. Получить список всех писем\n");
    printf("7. Обработать перемещение писем\n");
    printf("8. Выход\n");
    printf("Выберите опцию: ");
}

void print_error(SimulationStatus status) {
    switch (status) {
        case SIM_SUCCESS: break;
        case SIM_ERROR_NULL_PTR: printf("Ошибка: Нулевой указатель\n"); break;
        case SIM_ERROR_MEMORY: printf("Ошибка: Не удалось выделить память\n"); break;
        case SIM_ERROR_FILE: printf("Ошибка: Ошибка работы с файлом\n"); break;
        case SIM_ERROR_INVALID_ID: printf("Ошибка: Неверный ID\n"); break;
        default: printf("Ошибка: Неизвестная ошибка\n"); break;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Использование: %s <файл_связей> <файл_логов>\n", argv[0]);
        return 1;
    }
    
    Simulation sim;
    SimulationStatus status = simulation_init(&sim, argv[1], argv[2]);
    if (status != SIM_SUCCESS) {
        print_error(status);
        return 1;
    }
    
    printf("Почтовая система успешно инициализирована!\n");
    printf("Файл связей: %s\n", argv[1]);
    printf("Файл логов: %s\n", argv[2]);
    
    int running = 1;
    while (running) {
        print_menu();
        
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Неверный ввод\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1: {
                int id, capacity;
                printf("Введите ID отделения и вместимость: ");
                if (scanf("%d %d", &id, &capacity) == 2) {
                    status = simulation_add_office(&sim, id, capacity, NULL, 0);
                    if (status != SIM_SUCCESS) {
                        print_error(status);
                    } else {
                        printf("Отделение успешно добавлено\n");
                    }
                } else {
                    printf("Неверный ввод\n");
                }
                break;
            }
            
            case 2: {
                int office_id;
                printf("Введите ID отделения для удаления: ");
                if (scanf("%d", &office_id) == 1) {
                    status = simulation_remove_office(&sim, office_id);
                    if (status != SIM_SUCCESS) {
                        print_error(status);
                    } else {
                        printf("Отделение успешно удалено\n");
                    }
                } else {
                    printf("Неверный ввод\n");
                }
                break;
            }
            
            case 3: {
                int type, priority, from, to;
                char data[256];
                printf("Введите тип письма (0-ОБЫЧНОЕ, 1-СРОЧНОЕ), приоритет, откуда, куда: ");
                if (scanf("%d %d %d %d", &type, &priority, &from, &to) == 4) {
                    printf("Введите технические данные: ");
                    getchar();
                    fgets(data, sizeof(data), stdin);
                    data[strcspn(data, "\n")] = 0;
                    
                    status = simulation_add_letter(&sim, (LetterType)type, priority, from, to, data);
                    if (status != SIM_SUCCESS) {
                        print_error(status);
                    } else {
                        printf("Письмо успешно добавлено\n");
                    }
                } else {
                    printf("Неверный ввод\n");
                }
                break;
            }
            
            case 4: {
                int letter_id;
                printf("Введите ID письма для отметки как недоставленного: ");
                if (scanf("%d", &letter_id) == 1) {
                    status = simulation_mark_undelivered(&sim, letter_id);
                    if (status != SIM_SUCCESS) {
                        print_error(status);
                    } else {
                        printf("Письмо отмечено как недоставленное\n");
                    }
                } else {
                    printf("Неверный ввод\n");
                }
                break;
            }
            
            case 5: {
                int letter_id, office_id;
                printf("Введите ID письма и ID отделения: ");
                if (scanf("%d %d", &letter_id, &office_id) == 2) {
                    status = simulation_try_take_letter(&sim, letter_id, office_id);
                    if (status != SIM_SUCCESS) {
                        print_error(status);
                    } else {
                        printf("Письмо успешно получено\n");
                    }
                } else {
                    printf("Неверный ввод\n");
                }
                break;
            }
            
            case 6: {
                char filename[256];
                printf("Введите имя файла для сохранения: ");
                if (scanf("%255s", filename) == 1) {
                    status = simulation_save_letters_list(&sim, filename);
                    if (status != SIM_SUCCESS) {
                        print_error(status);
                    } else {
                        printf("Список писем сохранен в %s\n", filename);
                    }
                } else {
                    printf("Неверный ввод\n");
                }
                break;
            }
            
            case 7: {
                status = simulation_process_letters(&sim);
                if (status != SIM_SUCCESS) {
                    print_error(status);
                } else {
                    printf("Письма обработаны\n");
                }
                break;
            }
            
            case 8:
                running = 0;
                printf("Выход...\n");
                break;
                
            default:
                printf("Неверная опция\n");
                break;
        }
    }
    
    simulation_cleanup(&sim);
    return 0;
}
