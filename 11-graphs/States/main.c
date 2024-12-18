#define _CRT_SECURE_NO_WARNINGS

#include "graphsTests.h"
#include "graph.h"

#include <stdbool.h>
#include <stdio.h>

Graph* buildGraph(const char* fileName, bool* errorCode) {
    FILE* file = fopen(fileName, "r");
    int numberOfVertices = 0;
    fscanf(file, "%d ", &numberOfVertices);
    Graph* graph = createGraph(numberOfVertices, errorCode);
    if (*errorCode) {
        return NULL;
    }

    int numberOfEdges = 0;
    fscanf(file, "%d ", &numberOfEdges);
    int numberOfVerticesCreated = 0;
    //while (numberOfVerticesCreated < numberOfEdges) {

    //    fscanf(file, "%d ", &numberOfVertices);
    //}
}

int main(void) {
    bool errorCode = false;
    testGraph(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    
    Graph* graph = buildGraph("graphData.txt", &errorCode);
    if (errorCode) {
        return errorCode;
    }

    return errorCode;
}