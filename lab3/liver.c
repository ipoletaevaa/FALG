#include "liver.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#define UNUSED(x) (void)(x)

Liver* create_liver(unsigned int id, const char* surname, const char* name,
                   const char* patronymic, Date birth_date, char gender,
                   double average_income) {
    Liver* liver = (Liver*)malloc(sizeof(Liver));
    if (!liver) return NULL;
    liver->id = id;
    liver->surname = strdup(surname);
    liver->name = strdup(name);
    liver->patronymic = strdup(patronymic ? patronymic : "");
    liver->birth_date = birth_date;
    liver->gender = gender;
    liver->average_income = average_income;
    return liver;
}

void destroy_liver(Liver* liver) {
    if (liver) {
        free(liver->surname);
        free(liver->name);
        free(liver->patronymic);
        free(liver);
    }
}

void print_liver(const Liver* liver) {
    if (liver) {
        printf("ID: %u, Name: %s %s %s, Birth: %02d.%02d.%d, Gender: %c, Income: %.2f\n",
               liver->id, liver->surname, liver->name, liver->patronymic,
               liver->birth_date.day, liver->birth_date.month, liver->birth_date.year,
               liver->gender, liver->average_income);
    }
}

int compare_liver_by_age(const Liver* a, const Liver* b) {
    if (a->birth_date.year != b->birth_date.year) {
        return b->birth_date.year - a->birth_date.year;
    }
    if (a->birth_date.month != b->birth_date.month) {
        return b->birth_date.month - a->birth_date.month;
    }
    return b->birth_date.day - a->birth_date.day;
}

int is_valid_name(const char* name) {
    if (name == NULL || strlen(name) == 0) return 0;
    for (size_t i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i])) return 0;
    }
    return 1;
}

int is_valid_date(const Date* date) {
    if (date == NULL) return 0;
    if (date->year < 1900 || date->year > 2100) return 0;
    if (date->month < 1 || date->month > 12) return 0;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (date->year % 4 == 0 && (date->year % 100 != 0 || date->year % 400 == 0)) {
        days_in_month[1] = 29;
    }
    return date->day >= 1 && date->day <= days_in_month[date->month - 1];
}

int is_valid_gender(char gender) {
    return gender == 'M' || gender == 'W';
}

int is_valid_income(double income) {
    return income >= 0;
}

int compare_liver_by_id(const Liver* liver1, const Liver* liver2) {
    return (int)(liver1->id - liver2->id);
}

int compare_liver_by_name(const Liver* liver1, const Liver* liver2) {
    int cmp = strcmp(liver1->surname, liver2->surname);
    if (cmp != 0) return cmp;
    cmp = strcmp(liver1->name, liver2->name);
    if (cmp != 0) return cmp;
    return strcmp(liver1->patronymic, liver2->patronymic);
}

int compare_liver_by_income(const Liver* liver1, const Liver* liver2) {
    if (liver1->average_income < liver2->average_income) return -1;
    if (liver1->average_income > liver2->average_income) return 1;
    return 0;
}

Liver* load_liver_from_file(FILE* file, LiverStatus* status) {
    if (file == NULL) {
        if (status) *status = LIVER_ERROR_NULL_POINTER;
        return NULL;
    }
    Liver* liver = (Liver*)malloc(sizeof(Liver));
    if (!liver) {
        if (status) *status = LIVER_ERROR_MEMORY_ALLOCATION;
        return NULL;
    }
    char surname[100], name[100], patronymic[100];
    char gender;
    int day, month, year;
    if (fscanf(file, "%u %99s %99s %99s %d %d %d %c %lf",
               &liver->id, surname, name, patronymic,
               &day, &month, &year, &gender, &liver->average_income) != 9) {
        free(liver);
        if (status) *status = LIVER_ERROR_FILE_OPERATION;
        return NULL;
    }
    liver->birth_date.day = day;
    liver->birth_date.month = month;
    liver->birth_date.year = year;
    liver->gender = gender;
    liver->surname = strdup(surname);
    liver->name = strdup(name);
    liver->patronymic = strdup(patronymic);
    if (!is_valid_name(liver->surname) || !is_valid_name(liver->name) ||
        !is_valid_date(&liver->birth_date) || !is_valid_gender(liver->gender) ||
        !is_valid_income(liver->average_income)) {
        destroy_liver(liver);
        if (status) *status = LIVER_ERROR_INVALID_DATA;
        return NULL;
    }
    if (status) *status = LIVER_SUCCESS;
    return liver;
}

LiverStatus save_liver_to_file(const Liver* liver, FILE* file) {
    if (liver == NULL || file == NULL) {
        return LIVER_ERROR_NULL_POINTER;
    }
    fprintf(file, "%u %s %s %s %d %d %d %c %.2f\n",
            liver->id, liver->surname, liver->name, liver->patronymic,
            liver->birth_date.day, liver->birth_date.month, liver->birth_date.year,
            liver->gender, liver->average_income);
    return LIVER_SUCCESS;
}

LiverStatus load_livers_from_file(const char* filename, LinkedList** result) {
    if (filename == NULL || result == NULL) {
        return LIVER_ERROR_NULL_POINTER;
    }
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return LIVER_ERROR_FILE_OPERATION;
    }
    LinkedList* list;
    ListStatus list_status = create_list(&list);
    if (list_status != LIST_SUCCESS) {
        fclose(file);
        return LIVER_ERROR_MEMORY_ALLOCATION;
    }
    LiverStatus liver_status;
    Liver* liver;
    while ((liver = load_liver_from_file(file, &liver_status)) != NULL) {
        Node* current = list->head;
        size_t index = 0;
        while (current != NULL) {
            Liver* current_liver = (Liver*)current->data;
            if (compare_liver_by_age(liver, current_liver) >= 0) {
                break;
            }
            current = current->next;
            index++;
        }
        if (current == NULL) {
            push_back_list(list, liver);
        } else {
            insert_at_list(list, index, liver);
        }
    }
    fclose(file);
    *result = list;
    return LIVER_SUCCESS;
}

LiverStatus save_livers_to_file(const char* filename, const LinkedList* list) {
    if (filename == NULL || list == NULL) {
        return LIVER_ERROR_NULL_POINTER;
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return LIVER_ERROR_FILE_OPERATION;
    }
    Node* current = list->head;
    LiverStatus status = LIVER_SUCCESS;
    while (current != NULL && status == LIVER_SUCCESS) {
        status = save_liver_to_file((Liver*)current->data, file);
        current = current->next;
    }
    fclose(file);
    return status;
}

Liver* find_liver_by_id(const LinkedList* list, unsigned int id) {
    if (list == NULL) return NULL;
    Node* current = list->head;
    while (current != NULL) {
        Liver* liver = (Liver*)current->data;
        if (liver->id == id) {
            return liver;
        }
        current = current->next;
    }
    return NULL;
}

LinkedList* find_livers_by_name(const LinkedList* list, const char* name) {
    if (list == NULL || name == NULL) return NULL;
    LinkedList* result;
    if (create_list(&result) != LIST_SUCCESS) return NULL;
    Node* current = list->head;
    while (current != NULL) {
        Liver* liver = (Liver*)current->data;
        if (strcmp(liver->name, name) == 0 || strcmp(liver->surname, name) == 0) {
            push_back_list(result, liver);
        }
        current = current->next;
    }
    return result;
}

LinkedList* filter_livers_by_age(const LinkedList* list, int min_age, int max_age) {
    if (list == NULL) return NULL;
    LinkedList* result;
    if (create_list(&result) != LIST_SUCCESS) return NULL;
    time_t now = time(NULL);
    struct tm* current_time = localtime(&now);
    int current_year = current_time->tm_year + 1900;
    Node* current = list->head;
    while (current != NULL) {
        Liver* liver = (Liver*)current->data;
        int age = current_year - liver->birth_date.year;
        if (age >= min_age && age <= max_age) {
            push_back_list(result, liver);
        }
        current = current->next;
    }
    return result;
}

LinkedList* filter_livers_by_income(const LinkedList* list, double min_income, double max_income) {
    if (list == NULL) return NULL;
    LinkedList* result;
    if (create_list(&result) != LIST_SUCCESS) return NULL;
    Node* current = list->head;
    while (current != NULL) {
        Liver* liver = (Liver*)current->data;
        if (liver->average_income >= min_income && liver->average_income <= max_income) {
            push_back_list(result, liver);
        }
        current = current->next;
    }
    return result;
}

int calculate_age(const Liver* liver) {
    if (liver == NULL) return 0;
    time_t now = time(NULL);
    struct tm* current_time = localtime(&now);
    int current_year = current_time->tm_year + 1900;
    int current_month = current_time->tm_mon + 1;
    int current_day = current_time->tm_mday;
    int age = current_year - liver->birth_date.year;
    if (current_month < liver->birth_date.month ||
        (current_month == liver->birth_date.month && current_day < liver->birth_date.day)) {
        age--;
    }
    return age;
}

LiverStatus copy_liver(const Liver* source, Liver** destination) {
    if (source == NULL || destination == NULL) {
        return LIVER_ERROR_NULL_POINTER;
    }
    *destination = create_liver(source->id, source->surname, source->name,
                               source->patronymic, source->birth_date,
                               source->gender, source->average_income);
    if (*destination == NULL) {
        return LIVER_ERROR_MEMORY_ALLOCATION;
    }
    return LIVER_SUCCESS;
}
