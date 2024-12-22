#pragma once

#include <stdbool.h>

// A structure for storing vertices.
typedef struct Graph Graph;

// The value that is stored at the vertex.
typedef struct VertexValue {
    int key;
    int stateNumber;
    bool isCapital;
} VertexValue;

// Creates an array of vertices.
Graph* createGraph(int initialSizeOfGraph, bool* errorCode);

// Deletes the entire graph.
void deleteGraph(Graph** pointerToGraph, bool* errorCode);

// Adds a new vertex to the graph.
// The key for the node is set automatically and is equal to the number of nodes already added.
void addVertex(Graph* graph, VertexValue value, bool* errorCode);

// Connects two vertices.
void connectVertices(Graph* graph, int key1, int key2, int edgeWeight, bool* errorCode);

// Prints the adjacency matrix.
void printMatrix(Graph* graph);

// Sets the capital by the key.
void setCapital(Graph* graph, int key, bool* errorCode);

void addNearestCity(Graph* graph, const int city, bool* errorCode);