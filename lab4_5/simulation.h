#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdio.h>
#include "graph.h"
#include "post_office.h"
#include "letter.h"

typedef struct {
    PostOfficeArray offices;
    LetterArray letters;
    Graph connections;
    int next_letter_id;
    FILE *log_file;
} Simulation;

typedef enum {
    SIM_SUCCESS = 0,
    SIM_ERROR_NULL_PTR = 1,
    SIM_ERROR_MEMORY = 2,
    SIM_ERROR_FILE = 3,
    SIM_ERROR_INVALID_ID = 4
} SimulationStatus;

SimulationStatus simulation_init(Simulation *sim, const char *connections_file, const char *log_file);
void simulation_cleanup(Simulation *sim);
SimulationStatus simulation_add_office(Simulation *sim, int id, int capacity, const int *connected_ids, size_t connected_count);
SimulationStatus simulation_remove_office(Simulation *sim, int office_id);
SimulationStatus simulation_add_letter(Simulation *sim, LetterType type, int priority, int from_office, int to_office, const char *tech_data);
SimulationStatus simulation_mark_undelivered(Simulation *sim, int letter_id);
SimulationStatus simulation_try_take_letter(Simulation *sim, int letter_id, int office_id);
SimulationStatus simulation_process_letters(Simulation *sim);
SimulationStatus simulation_save_letters_list(Simulation *sim, const char *filename);

#endif
