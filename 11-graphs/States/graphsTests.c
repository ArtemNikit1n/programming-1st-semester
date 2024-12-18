#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

void testCreateAndDelete(bool* errorCode) {
    VertexValue value1 = { .stateNumber = 0, .isCapital = false };
    VertexValue value2 = { .stateNumber = 1, .isCapital = true };

    Graph* testGraph = createGraph(value1, errorCode);
    addVertex(testGraph, value2, errorCode);
    deleteGraph(&testGraph, errorCode);
}

void testConnectVertices(bool* errorCode) {
    VertexValue value1 = { .stateNumber = 0, .isCapital = false };
    VertexValue value2 = { .stateNumber = 1, .isCapital = true };
    VertexValue value3 = { .stateNumber = 2, .isCapital = true };

    Graph* testGraph = createGraph(value1, errorCode);
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