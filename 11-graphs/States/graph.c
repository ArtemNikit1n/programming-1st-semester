#include "graph.h"

#include <stdlib.h>

typedef struct Vertex {
    VertexValue value;
    int numberOfAdjacentVertices;
    struct Vertex** adjacentVertices;
} Vertex;

struct Graph {
    int numberVertices;
    Vertex** vertices;
};

Vertex* createVertex(VertexValue value, bool* errorCode) {
    Vertex* vertex = calloc(1, sizeof(Vertex));
    if (vertex == NULL) {
        *errorCode = true;
        return NULL;
    }

    vertex->value = value;
    return vertex;
}

void addVertex(Graph* graph, VertexValue value, bool* errorCode) {
    Vertex** newMemory = realloc(graph->vertices, (graph->numberVertices + 1) * sizeof(Vertex*));
    if (newMemory == NULL) {
        *errorCode = true;
        return;
    }

    graph->vertices = newMemory;
    graph->vertices[graph->numberVertices] = createVertex(value, errorCode);
    ++graph->numberVertices;
}

void addVertexToListOfAdjacentOnes(Vertex* vertex, Vertex* newVertex, bool* errorCode) {
    if (vertex->adjacentVertices == NULL) {
        vertex->adjacentVertices = calloc(1, sizeof(Vertex*));
        if (vertex->adjacentVertices == NULL) {
            *errorCode = true;
            return;
        }
        vertex->adjacentVertices[0] = newVertex;

        ++vertex->numberOfAdjacentVertices;
    }
    else {
        Vertex** newMemory = realloc(vertex->adjacentVertices, (vertex->numberOfAdjacentVertices + 1) * sizeof(Vertex*));
        if (newMemory == NULL) {
            *errorCode = true;
            return;
        }

        vertex->adjacentVertices = newMemory;
        vertex->adjacentVertices[vertex->numberOfAdjacentVertices] = newVertex;
        ++vertex->numberOfAdjacentVertices;
    }
}

void connectVertices(Graph* graph, int key1, int key2, bool* errorCode) {
    if (graph == NULL) {
        *errorCode = true;
        return;
    }

    if (key1 >= graph->numberVertices || key2 >= graph->numberVertices) {
        *errorCode = true;
        return;
    }

    Vertex* vertex1 = graph->vertices[key1];
    Vertex* vertex2 = graph->vertices[key2];

    addVertexToListOfAdjacentOnes(vertex1, vertex2, errorCode);
    if (*errorCode) {
        return;
    }
    addVertexToListOfAdjacentOnes(vertex2, vertex1, errorCode);
    if (*errorCode) {
        return;
    }
}

Graph* createGraph(VertexValue value, bool* errorCode) {
    Graph* graph = calloc(1, sizeof(Graph));
    if (graph == NULL) {
        *errorCode = true;
        return NULL;
    }

    graph->numberVertices = 1;

    Vertex** vertices = calloc(1, sizeof(Vertex));
    if (vertices == NULL) {
        *errorCode = true;
        return NULL;
    }

    vertices[0] = createVertex(value, errorCode);
    graph->vertices = vertices;

    return graph;
}

void deleteGraph(Graph** pointerToGraph, bool* errorCode) {
    if (*pointerToGraph == NULL) {
        *errorCode = true;
        return;
    }

    for (int i = 0; i < (*pointerToGraph)->numberVertices; ++i) {
        free((*pointerToGraph)->vertices[i]);
    }
    free(*pointerToGraph);
    pointerToGraph = NULL;
}