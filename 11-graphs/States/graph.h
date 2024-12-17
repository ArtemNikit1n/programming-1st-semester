#pragma once

#include <stdbool.h>

// To get a vertex, you need to refer to the graph as an array. 
// The index will be the vertex number.
// The vertex number corresponds to the order in which it was added (numbering from zero).
typedef struct Graph* Graph;

// The vertex of the graph.
typedef struct Vertex* Vertex;

// The value that is stored at the vertex.
typedef struct VertexValue {
    int stateNumber;
    bool isCapital;
} VertexValue;


// Creates an array of vertices.
void createGraph(Vertex* vertex, bool* errorCode);

// Deletes the entire graph.
void deleteGraph(Graph* graph, bool* errorCode);

Vertex* createVertex(VertexValue value, bool* errorCode);

// Adds a new vertex to the graph.
void addVertex(VertexValue value, bool* errorCode);

// Allows you to find out the value at the vertex.
VertexValue getVertexValue(Vertex* vertex, bool* errorCode);

// Connects two vertices.
void connectVertices(Vertex* vertex, Vertex* newVertex, bool* errorCode);