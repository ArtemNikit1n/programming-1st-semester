#include "graph.h"

#include <stdlib.h>

typedef struct Edge {
    int weight;
    Vertex* adjacentVertex;
} Edge;

struct Graph {
    int numberVertices;
    Vertex* vertices;
};

struct Vertex {
    VertexValue value;
    Edge* adjacentVertices;
};

void createGraph(Vertex* vertex, bool* errorCode) {
    Graph graph = calloc(1, sizeof(Graph));
    if (graph == NULL) {
        *errorCode = true;
        return;
    }

    graph->numberVertices = 1;

    Vertex* vertices = calloc(1, sizeof(Vertex));
    if (vertices == NULL) {
        *errorCode = true;
        return;
    }

    vertices[0] = vertex;
    graph->vertices = vertices;
}

Vertex* createVertex(VertexValue value, bool* errorCode) {
    Vertex vertex = calloc(1, sizeof(Vertex));
    if (vertex == NULL) {
        *errorCode = true;
        return NULL;
    }

    vertex->value = value;
    return vertex;
}
