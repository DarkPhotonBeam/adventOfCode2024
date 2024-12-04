//
// Created by dan on 12/4/24.
//

#ifndef GRAPH_H
#define GRAPH_H
#include "arrayList.h"

typedef struct {
    size_t size;
    array_list **adj;
    short directed;
} graph_t;

graph_t *gr_create(const size_t size, short directed);

void gr_addEdge(graph_t *graph, int u, int v);

void gr_bfs(graph_t *graph, int root);

void gr_destroy(graph_t *graph);

#endif //GRAPH_H
