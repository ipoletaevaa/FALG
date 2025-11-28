#include "../include/graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Graph graph_create(size_t capacity) {
    Graph graph;
    graph.connections = NULL;
    graph.size = 0;
    graph.capacity = 0;
    
    if (capacity > 0) {
        graph.connections = (Connection*)calloc(capacity, sizeof(Connection));
        if (graph.connections != NULL) {
            graph.capacity = capacity;
        }
    }
    
    return graph;
}

void graph_destroy(Graph *graph) {
    if (graph != NULL) {
        free(graph->connections);
        graph->connections = NULL;
        graph->size = 0;
        graph->capacity = 0;
    }
}

int graph_add_connection(Graph *graph, int office1_id, int office2_id) {
    if (graph == NULL) {
        return 0;
    }
    
    if (graph->size >= graph->capacity) {
        size_t new_capacity = graph->capacity * 2;
        if (new_capacity == 0) new_capacity = 10;
        
        Connection *new_connections = (Connection*)realloc(graph->connections, new_capacity * sizeof(Connection));
        if (new_connections == NULL) {
            return 0;
        }
        
        graph->connections = new_connections;
        graph->capacity = new_capacity;
    }
    
    graph->connections[graph->size].office1_id = office1_id;
    graph->connections[graph->size].office2_id = office2_id;
    graph->size++;
    
    return 1;
}

int graph_load_from_file(Graph *graph, const char *filename) {
    if (graph == NULL || filename == NULL) {
        return 0;
    }
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    
    int office1_id, office2_id;
    while (fscanf(file, "%d,%d", &office1_id, &office2_id) == 2) {
        if (!graph_add_connection(graph, office1_id, office2_id)) {
            fclose(file);
            return 0;
        }
    }
    
    fclose(file);
    return 1;
}

int graph_are_connected(const Graph *graph, int office1_id, int office2_id) {
    if (graph == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < graph->size; i++) {
        Connection conn = graph->connections[i];
        if ((conn.office1_id == office1_id && conn.office2_id == office2_id) ||
            (conn.office1_id == office2_id && conn.office2_id == office1_id)) {
            return 1;
        }
    }
    
    return 0;
}

int* graph_get_connections(const Graph *graph, int office_id, size_t *count) {
    if (graph == NULL || count == NULL) {
        return NULL;
    }
    
    *count = 0;
    int *connections = (int*)malloc(graph->size * sizeof(int));
    if (connections == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < graph->size; i++) {
        Connection conn = graph->connections[i];
        if (conn.office1_id == office_id) {
            connections[(*count)++] = conn.office2_id;
        } else if (conn.office2_id == office_id) {
            connections[(*count)++] = conn.office1_id;
        }
    }
    
    return connections;
}