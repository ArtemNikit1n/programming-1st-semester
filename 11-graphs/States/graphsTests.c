#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

void testCreateAndDelete(bool* errorCode) {
    VertexValue value1 = { .key = 0, .stateNumber = 0, .isCapital = false };
    VertexValue value2 = { .key = 1, .stateNumber = 1, .isCapital = true };

    Graph* testGraph = createGraph(5, errorCode);
    addVertex(testGraph, value1, errorCode);
    addVertex(testGraph, value2, errorCode);
    deleteGraph(&testGraph, errorCode);
}

void testConnectVertices(bool* errorCode) {
    VertexValue value1 = { .key = 0, .stateNumber = 0, .isCapital = false };
    VertexValue value2 = { .key = 1, .stateNumber = 1, .isCapital = true };
    VertexValue value3 = { .key = 2, .stateNumber = 2, .isCapital = true };

    Graph* testGraph = createGraph(2, errorCode);
    addVertex(testGraph, value1, errorCode);
    addVertex(testGraph, value2, errorCode);
    addVertex(testGraph, value3, errorCode);

    connectVertices(testGraph, 0, 2, errorCode);
    connectVertices(testGraph, 0, 1, errorCode);

    deleteGraph(&testGraph, errorCode);
}

void testGraph(bool* errorCode) {
    testCreateAndDelete(errorCode);
    testConnectVertices(errorCode);
}