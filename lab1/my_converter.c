#include "converter.h"

ConverterStatus decimal_to_base_2r(int number, int r, char** result){//ConverterStatus забыла!!!
    if (result == NULL) return CONVERT_ERROR_NULL_PTR; //проверяем указатель, а не number 
    if (r < 1 || r > 5) return CONVERT_ERROR_INVALID_R;

    //Проерили валидность
    //Выделим место под нулевую строку
    //Создадим маску
    //Создадим буфер для записи с нужным размером 
    //Запишем в бефер в правильном порядке 
    //Уберём мусор из буфера с помощью указателя на начало строки значащего


    if (number == 0){
        //Можно написать malloc(2)
        char* temp = malloc(2 * sizeof(char));//sizeof(char) = 1 всегда
        temp[0] = '0';
        temp[1] = '\0';
        *result = temp;//забыла передать результат
        return CONVERT_SUCCESS;//забыла объявить конец
    }

    unsigned int mask = (1u << r) - 1u; // 00010000 - 1 = 00001111
    //int num2 = number; так делаем только для битового сдвига
    int in_otr = 0;

    unsigned int n;//нужен здесь, чтобы не менять исходное число
    if (number < 0){
        in_otr = 1;
        n = (unsigned int)(-number);
    }else{
        n = (unsigned int)(number);
    }

    int max_len = (32 / r) + 3;
    char* buffer = malloc(max_len * sizeof(char));
    if (buffer == NULL) return CONVERT_ERROR_ALLOCATION;
    unsigned int index = max_len - 1;
    unsigned int num2 = number;

    while (num2 > 0){
        index--;
        //прогоним через маску и добавим числа
        unsigned int digit = num2 & mask; //не указала тип и не поняла, что просто число тут берём 
        if (digit < 10){
            buffer[index] = '0' + digit;
        }else{
            buffer[index] = 'A' + (digit - 10);//цифры 10-15 символы A-F поэтому нужен сдвиг
        }

        num2 = num2 >> r; //забыла сдвиг добавить
    }

    buffer[max_len - 1] = '\0';
    if (in_otr){
        index--;
        buffer[index] = '-';
    }

    char* result_str = malloc((max_len - index) * sizeof(char)); //проверку на пустой буфер надо при ошибке, забыль 
    if (result_str == NULL) return CONVERT_ERROR_ALLOCATION;

    char* str = &buffer[index]; //забыла &, buffer[index] это char, не char*, берём адрес начала строки 
    char* dtr = result_str; //указаетль должен быть на что-то -> на выделенную память (которую я забыла выделить)
    while (*str){
        *dtr++ = *str++;
    }
    *dtr = '\0'; //забыла терминирующий ноль добавить
    *result = result_str;
    free(buffer); //очищаем всю выделенную временную память
    return CONVERT_SUCCESS;
    
}
