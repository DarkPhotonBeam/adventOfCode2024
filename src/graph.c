//
// Created by dan on 12/4/24.
//

#include "graph.h"

#include <stdio.h>

#include "linkedList.h"

graph_t *gr_create(const size_t size, short directed) {
    graph_t *graph = malloc(sizeof(graph_t));
    graph->size = size;
    graph->adj = malloc(size * sizeof(void *));
    for (size_t i = 0; i < size; ++i) {
        graph->adj[i] = NULL;
    }
    graph->directed = directed;
    return graph;
}

int gr_containsVertex(graph_t *graph, int u) {
    return graph->adj[u] != NULL;
}

void gr_addVertex(graph_t *graph, int u) {
    if (!gr_containsVertex(graph, u)) {
        graph->adj[u] = al_create();
    }
}

void gr_addEdge(graph_t *graph, int u, int v) {
    gr_addVertex(graph, u);
    gr_addVertex(graph, v);
    al_pushInt(graph->adj[u], v);
    if (graph->directed) al_pushInt(graph->adj[v], u);
}

void gr_bfs(graph_t *graph, int root) {
    int *visited = malloc( graph->size * sizeof(int) );
    for (size_t i = 0; i < graph->size; i++) visited[i] = 0;
    linked_list *queue = ll_create();
    ll_addInt(queue, root);
    visited[root] = 1;

    while (!ll_isEmpty(queue)) {
        const int u = ll_removeFirst(queue).intVal;
        printf("dequeued %d\n", u);
        const array_list *uN = graph->adj[u];

        for (size_t i = 0; i < uN->size; ++i) {
            const int v = al_get(uN, i).intVal;
            if (visited[v]) continue;
            visited[v] = 1;
            ll_addInt(queue, v);
        }
    }

    free(visited);
    ll_destroy(queue);
}

void gr_destroy(graph_t *graph) {
    for (int i = 0; i < graph->size; ++i) {
        if (graph->adj[i] == NULL) continue;
        free(graph->adj[i]);
    }
    free(graph->adj);
}