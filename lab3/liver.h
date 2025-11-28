#ifndef LIVER_H
#define LIVER_H

#include <stddef.h>
#include <stdio.h>
#include "linked_list.h"

typedef struct {
    int day;
    int month; 
    int year;
} Date;

typedef struct {
    unsigned int id;
    char* surname;
    char* name;
    char* patronymic;
    Date birth_date;
    char gender;
    double average_income;
} Liver;

typedef enum {
    LIVER_SUCCESS = 0,
    LIVER_ERROR_NULL_POINTER,
    LIVER_ERROR_INVALID_ID,
    LIVER_ERROR_INVALID_NAME,
    LIVER_ERROR_INVALID_DATE,
    LIVER_ERROR_INVALID_GENDER,
    LIVER_ERROR_INVALID_INCOME,
    LIVER_ERROR_MEMORY_ALLOCATION,
    LIVER_ERROR_FILE_OPERATION,
    LIVER_ERROR_INVALID_DATA
} LiverStatus;

Liver* create_liver(unsigned int id, const char* surname, const char* name, 
                   const char* patronymic, Date birth_date, char gender, 
                   double average_income);
void destroy_liver(Liver* liver);
int is_valid_name(const char* name);
int is_valid_date(const Date* date);
int is_valid_gender(char gender);
int is_valid_income(double income);

int compare_liver_by_age(const Liver* liver1, const Liver* liver2);
int compare_liver_by_id(const Liver* liver1, const Liver* liver2);
int compare_liver_by_name(const Liver* liver1, const Liver* liver2);
int compare_liver_by_income(const Liver* liver1, const Liver* liver2);

Liver* load_liver_from_file(FILE* file, LiverStatus* status);
LiverStatus save_liver_to_file(const Liver* liver, FILE* file);
LiverStatus load_livers_from_file(const char* filename, LinkedList** result);
LiverStatus save_livers_to_file(const char* filename, const LinkedList* list);

Liver* find_liver_by_id(const LinkedList* list, unsigned int id);
LinkedList* find_livers_by_name(const LinkedList* list, const char* name);
LinkedList* filter_livers_by_age(const LinkedList* list, int min_age, int max_age);
LinkedList* filter_livers_by_income(const LinkedList* list, double min_income, double max_income);

void print_liver(const Liver* liver);
int calculate_age(const Liver* liver);
LiverStatus copy_liver(const Liver* source, Liver** destination);

#endif
