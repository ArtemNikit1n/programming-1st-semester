#include "graph.h"

typedef struct VertexValue {
    int stateNumber;
    bool isCapital;
} VertexValue;

typedef struct Edge {
    int weight;
    Vertex *adjacentVertex;
    Edge *nextEdge;
} Edge;

typedef struct Vertex {
    VertexValue value;
    Edge *adjacentVertices;
} Vertex;

struct Graph {
    Vertex* vertices;
};