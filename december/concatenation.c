#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stddef.h>

// конкатенация строк

int concatenation(char** result, char* first, ...){
    if (result == NULL) return 1;
    if (first == NULL) return 2;
    
    // Инициализировали список переменных аргументов
    va_list args;
    va_start(args, first);
    size_t total_length = strlen(first);

    char* current = va_arg(args, char*);

    while (current != NULL){ //Посчитали всю длину
        total_length += strlen(current);
        current = va_arg(args, char*);
    }

    //Надо выделить память 
    // Куда надо положить результат, зачем выделять память? 
    *result = malloc((total_length + 1) * sizeof(char));
    if (*result == NULL) return 3;
    // Нужно в неё скопировать строки
    // Как копируем: вот у нас есть память просто, мы используем strcpy
    // Мы двигаем указатель по памяти сами, чтобы всё копировалось в нужное место 
    char* pos = *result;

    va_start(args, first);
    strcpy(pos, first);
    pos += strlen(first);

    while ((current = va_arg(args, char*)) != NULL){
        strcpy(pos, current);
        pos += strlen(current);
    }

    va_end(args);

    return 0;
}


int main(){
    char* result;
    int status = concatenation(&result, "Дашка", " Милашка", NULL);
    printf("%s %d", result, status);

    free(result);
}