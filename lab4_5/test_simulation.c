#include "../include/simulation.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_simulation_init_cleanup() {
    Simulation sim;
    
    FILE *test_file = fopen("test_connections.txt", "w");
    fprintf(test_file, "1,2\n2,3\n1,3\n");
    fclose(test_file);
    
    SimulationStatus status = simulation_init(&sim, "test_connections.txt", "test_log.txt");
    assert(status == SIM_SUCCESS);
    assert(sim.offices.size == 0);
    assert(sim.letters.size == 0);
    assert(sim.connections.size == 3);
    assert(sim.log_file != NULL);
    
    simulation_cleanup(&sim);
    
    remove("test_connections.txt");
    remove("test_log.txt");
    printf("test_simulation_init_cleanup: ПРОЙДЕН\n");
}

void test_simulation_add_office() {
    Simulation sim;
    
    FILE *test_file = fopen("test_connections.txt", "w");
    fprintf(test_file, "1,2\n");
    fclose(test_file);
    
    simulation_init(&sim, "test_connections.txt", "test_log.txt");
    
    SimulationStatus status = simulation_add_office(&sim, 1, 10, NULL, 0);
    assert(status == SIM_SUCCESS);
    assert(sim.offices.size == 1);
    assert(sim.offices.offices[0].id == 1);
    assert(sim.offices.offices[0].capacity == 10);
    
    status = simulation_add_office(&sim, 1, 5, NULL, 0);
    assert(status == SIM_ERROR_INVALID_ID);
    
    simulation_cleanup(&sim);
    
    remove("test_connections.txt");
    remove("test_log.txt");
    printf("test_simulation_add_office: ПРОЙДЕН\n");
}

void test_simulation_add_letter() {
    Simulation sim;
    
    FILE *test_file = fopen("test_connections.txt", "w");
    fprintf(test_file, "1,2\n");
    fclose(test_file);
    
    simulation_init(&sim, "test_connections.txt", "test_log.txt");
    simulation_add_office(&sim, 1, 10, NULL, 0);
    simulation_add_office(&sim, 2, 10, NULL, 0);
    
    SimulationStatus status = simulation_add_letter(&sim, LETTER_REGULAR, 1, 1, 2, "test_data");
    assert(status == SIM_SUCCESS);
    assert(sim.letters.size == 1);
    assert(sim.letters.letters[0].from_office == 1);
    assert(sim.letters.letters[0].to_office == 2);
    assert(sim.letters.letters[0].priority == 1);
    assert(strcmp(sim.letters.letters[0].technical_data, "test_data") == 0);
    
    status = simulation_add_letter(&sim, LETTER_URGENT, 2, 3, 4, "invalid");
    assert(status == SIM_ERROR_INVALID_ID);
    
    simulation_cleanup(&sim);
    
    remove("test_connections.txt");
    remove("test_log.txt");
    printf("test_simulation_add_letter: ПРОЙДЕН\n");
}

int main() {
    printf("Запуск тестов симуляции...\n");
    
    test_simulation_init_cleanup();
    test_simulation_add_office();
    test_simulation_add_letter();
    
    printf("Все тесты симуляции ПРОЙДЕНЫ!\n");
    return 0;
}
