#include "../include/simulation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

SimulationStatus simulation_init(Simulation *sim, const char *connections_file, const char *log_file) {
    if (sim == NULL || connections_file == NULL || log_file == NULL) {
        return SIM_ERROR_NULL_PTR;
    }
    
    sim->offices = post_office_array_create(0);
    sim->letters = letter_array_create(0);
    sim->connections = graph_create(0);
    sim->next_letter_id = 1;
    sim->log_file = NULL;
    
    if (!graph_load_from_file(&sim->connections, connections_file)) {
        simulation_cleanup(sim);
        return SIM_ERROR_FILE;
    }
    
    sim->log_file = fopen(log_file, "w");
    if (sim->log_file == NULL) {
        simulation_cleanup(sim);
        return SIM_ERROR_FILE;
    }
    
    fprintf(sim->log_file, "=== Лог симуляции почтовой системы ===\n");
    fprintf(sim->log_file, "Начало: %ld\n", (long)time(NULL));
    fflush(sim->log_file);
    
    return SIM_SUCCESS;
}

void simulation_cleanup(Simulation *sim) {
    if (sim != NULL) {
        if (sim->log_file != NULL) {
            fprintf(sim->log_file, "Завершение симуляции: %ld\n", (long)time(NULL));
            fclose(sim->log_file);
            sim->log_file = NULL;
        }
        
        post_office_array_destroy(&sim->offices);
        letter_array_destroy(&sim->letters);
        graph_destroy(&sim->connections);
    }
}

SimulationStatus simulation_add_office(Simulation *sim, int id, int capacity, const int *connected_ids, size_t connected_count) {
    if (sim == NULL) {
        return SIM_ERROR_NULL_PTR;
    }
    
    if (post_office_array_get(&sim->offices, id) != NULL) {
        return SIM_ERROR_INVALID_ID;
    }
    
    PostOffice office;
    office.id = id;
    office.capacity = capacity;
    office.connected_offices = NULL;
    office.connected_count = 0;
    office.connected_capacity = 0;
    
    if (heap_create(&office.letters_heap, capacity) != HEAP_SUCCESS) {
        return SIM_ERROR_MEMORY;
    }
    
    for (size_t i = 0; i < connected_count; i++) {
        if (!post_office_add_connection(&office, connected_ids[i])) {
            heap_destroy(&office.letters_heap);
            return SIM_ERROR_MEMORY;
        }
    }
    
    if (!post_office_array_add(&sim->offices, &office)) {
        heap_destroy(&office.letters_heap);
        free(office.connected_offices);
        return SIM_ERROR_MEMORY;
    }
    
    fprintf(sim->log_file, "Добавлено отделение %d с вместимостью %d\n", id, capacity);
    fflush(sim->log_file);
    
    return SIM_SUCCESS;
}

SimulationStatus simulation_remove_office(Simulation *sim, int office_id) {
    if (sim == NULL) {
        return SIM_ERROR_NULL_PTR;
    }
    
    PostOffice *office = post_office_array_get(&sim->offices, office_id);
    if (office == NULL) {
        return SIM_ERROR_INVALID_ID;
    }
    
    for (size_t i = 0; i < sim->letters.size; i++) {
        Letter *letter = &sim->letters.letters[i];
        if (letter->from_office == office_id || letter->to_office == office_id) {
            if (letter->state == LETTER_IN_TRANSIT) {
                letter->state = LETTER_UNDELIVERED;
                fprintf(sim->log_file, "Письмо %d отмечено как недоставленное (удалено отделение %d)\n", 
                       letter->id, office_id);
            }
        }
    }
    
    for (size_t i = 0; i < sim->offices.size; i++) {
        if (sim->offices.offices[i].id == office_id) {
            heap_destroy(&sim->offices.offices[i].letters_heap);
            free(sim->offices.offices[i].connected_offices);
            
            for (size_t j = i; j < sim->offices.size - 1; j++) {
                sim->offices.offices[j] = sim->offices.offices[j + 1];
            }
            sim->offices.size--;
            
            fprintf(sim->log_file, "Удалено отделение %d\n", office_id);
            fflush(sim->log_file);
            return SIM_SUCCESS;
        }
    }
    
    return SIM_ERROR_INVALID_ID;
}

SimulationStatus simulation_add_letter(Simulation *sim, LetterType type, int priority, 
                                      int from_office, int to_office, const char *tech_data) {
    if (sim == NULL || tech_data == NULL) {
        return SIM_ERROR_NULL_PTR;
    }
    
    if (post_office_array_get(&sim->offices, from_office) == NULL ||
        post_office_array_get(&sim->offices, to_office) == NULL) {
        return SIM_ERROR_INVALID_ID;
    }
    
    Letter letter;
    letter.id = sim->next_letter_id++;
    letter.type = type;
    letter.state = LETTER_IN_TRANSIT;
    letter.priority = priority;
    letter.from_office = from_office;
    letter.to_office = to_office;
    strncpy(letter.technical_data, tech_data, sizeof(letter.technical_data) - 1);
    letter.technical_data[sizeof(letter.technical_data) - 1] = '\0';
    
    if (!letter_array_add(&sim->letters, &letter)) {
        return SIM_ERROR_MEMORY;
    }
    
    PostOffice *from_office_ptr = post_office_array_get(&sim->offices, from_office);
    if (!post_office_add_letter(from_office_ptr, &letter)) {
        sim->letters.size--;
        return SIM_ERROR_MEMORY;
    }
    
    fprintf(sim->log_file, "Добавлено письмо %d из отделения %d в отделение %d (приоритет: %d)\n",
           letter.id, from_office, to_office, priority);
    fflush(sim->log_file);
    
    return SIM_SUCCESS;
}

SimulationStatus simulation_mark_undelivered(Simulation *sim, int letter_id) {
    if (sim == NULL) {
        return SIM_ERROR_NULL_PTR;
    }
    
    Letter *letter = letter_array_get(&sim->letters, letter_id);
    if (letter == NULL) {
        return SIM_ERROR_INVALID_ID;
    }
    
    letter->state = LETTER_UNDELIVERED;
    
    fprintf(sim->log_file, "Письмо %d отмечено как недоставленное\n", letter_id);
    fflush(sim->log_file);
    
    return SIM_SUCCESS;
}

SimulationStatus simulation_try_take_letter(Simulation *sim, int letter_id, int office_id) {
    if (sim == NULL) {
        return SIM_ERROR_NULL_PTR;
    }
    
    Letter *letter = letter_array_get(&sim->letters, letter_id);
    if (letter == NULL) {
        return SIM_ERROR_INVALID_ID;
    }
    
    if (letter->to_office != office_id) {
        return SIM_ERROR_INVALID_ID;
    }
    
    if (letter->state != LETTER_IN_TRANSIT) {
        return SIM_ERROR_INVALID_ID;
    }
    
    letter->state = LETTER_DELIVERED;
    
    fprintf(sim->log_file, "Письмо %d доставлено в отделение %d\n", letter_id, office_id);
    fflush(sim->log_file);
    
    return SIM_SUCCESS;
}

SimulationStatus simulation_process_letters(Simulation *sim) {
    if (sim == NULL) {
        return SIM_ERROR_NULL_PTR;
    }
    
    fprintf(sim->log_file, "Обработка перемещения писем...\n");
    
    for (size_t i = 0; i < sim->offices.size; i++) {
        PostOffice *office = &sim->offices.offices[i];
        
        int is_empty;
        heap_is_empty(&office->letters_heap, &is_empty);
        if (is_empty) {
            continue;
        }
        
        int priority;
        if (heap_peek(&office->letters_heap, &priority) == HEAP_SUCCESS) {
            for (size_t j = 0; j < sim->letters.size; j++) {
                Letter *letter = &sim->letters.letters[j];
                if (letter->priority == priority && letter->state == LETTER_IN_TRANSIT) {
                    fprintf(sim->log_file, "Письмо %d перемещено из отделения %d\n", 
                           letter->id, office->id);
                    break;
                }
            }
        }
    }
    
    fflush(sim->log_file);
    return SIM_SUCCESS;
}

SimulationStatus simulation_save_letters_list(Simulation *sim, const char *filename) {
    if (sim == NULL || filename == NULL) {
        return SIM_ERROR_NULL_PTR;
    }
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return SIM_ERROR_FILE;
    }
    
    fprintf(file, "=== Список писем ===\n");
    fprintf(file, "ID\tТип\tСтатус\tПриоритет\tОткуда\tКуда\tДанные\n");
    
    for (size_t i = 0; i < sim->letters.size; i++) {
        const Letter *letter = &sim->letters.letters[i];
        
        const char *type_str = (letter->type == LETTER_REGULAR) ? "ОБЫЧНОЕ" : "СРОЧНОЕ";
        const char *state_str = "НЕИЗВЕСТНО";
        switch (letter->state) {
            case LETTER_IN_TRANSIT: state_str = "В_ПУТИ"; break;
            case LETTER_DELIVERED: state_str = "ДОСТАВЛЕНО"; break;
            case LETTER_UNDELIVERED: state_str = "НЕДОСТАВЛЕНО"; break;
        }
        
        fprintf(file, "%d\t%s\t%s\t%d\t%d\t%d\t%s\n",
               letter->id, type_str, state_str, letter->priority,
               letter->from_office, letter->to_office, letter->technical_data);
    }
    
    fclose(file);
    return SIM_SUCCESS;
}