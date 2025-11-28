#ifndef GRAPH_H
#define GRAPH_H

#include "post_office.h"

typedef struct {
    int office1_id;
    int office2_id;
} Connection;

typedef struct {
    Connection *connections;
    size_t size;
    size_t capacity;
} Graph;

Graph graph_create(size_t capacity);
void graph_destroy(Graph *graph);
int graph_add_connection(Graph *graph, int office1_id, int office2_id);
int graph_load_from_file(Graph *graph, const char *filename);
int graph_are_connected(const Graph *graph, int office1_id, int office2_id);
int* graph_get_connections(const Graph *graph, int office_id, size_t *count);

#endif
