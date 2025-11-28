#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <входной_файл>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    interpreter_status_t status = interpreter_execute_file(argv[1]);
    
    switch (status) {
        case INTERPRETER_SUCCESS:
            return EXIT_SUCCESS;
            
        case INTERPRETER_FILE_ERROR:
            fprintf(stderr, "Ошибка: Не удается открыть файл '%s'\n", argv[1]);
            return EXIT_FAILURE;
            
        case INTERPRETER_SYNTAX_ERROR:
            fprintf(stderr, "Ошибка: Синтаксическая ошибка во входном файле\n");
            return EXIT_FAILURE;
            
        case INTERPRETER_MEMORY_ERROR:
            fprintf(stderr, "Ошибка: Не удалось выделить память\n");
            return EXIT_FAILURE;
            
        case INTERPRETER_NULL_POINTER:
            fprintf(stderr, "Ошибка: Внутренняя ошибка нулевого указателя\n");
            return EXIT_FAILURE;
            
        default:
            fprintf(stderr, "Ошибка: Произошла неизвестная ошибка\n");
            return EXIT_FAILURE;
    }
}