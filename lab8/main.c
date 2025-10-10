#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_processor.h"
#include "number_converter.h"
#include "validation.h"

int main() {
    int base;
    printf("Введите основание системы счисления (2-36): ");
    
    if (scanf("%d", &base) != 1) {
        printf("Ошибка: некорректный ввод основания\n");
        return EXIT_FAILURE;
    }
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (!is_valid_base(base)) {
        printf("Ошибка: основание должно быть в диапазоне [2..36]\n");
        return EXIT_FAILURE;
    }

    long long max_number;
    char* max_number_str = NULL;

    ProcessorStatus status = process_user_input(base, &max_number, &max_number_str);
    
    if (status == PROCESSOR_STOP_SIGNAL || max_number_str == NULL) {
        printf("Не было введено ни одного числа\n");
        return EXIT_SUCCESS;
    } else if (status != PROCESSOR_SUCCESS) {
        printf("Ошибка обработки ввода\n");
        return EXIT_FAILURE;
    }

    printf("\nРезультаты:\n");
    printf("Максимальное по модулю число: %s\n", max_number_str);


    int target_bases[] = {9, 18, 27, 36};
    int num_bases = sizeof(target_bases) / sizeof(target_bases[0]);

    for (int i = 0; i < num_bases; i++) {
        char* converted = NULL;
        ConverterStatus conv_status = convert_to_base(max_number, target_bases[i], &converted);
        
        if (conv_status == CONVERTER_SUCCESS && converted) {
            printf("В системе с основанием %d: %s\n", target_bases[i], converted);
            free(converted);
        } else {
            printf("В системе с основанием %d: ошибка конвертации\n", target_bases[i]);
        }
    }

    free(max_number_str);
    return EXIT_SUCCESS;
}