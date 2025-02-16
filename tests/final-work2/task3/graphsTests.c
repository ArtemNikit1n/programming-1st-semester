#define _CRT_SECURE_NO_WARNINGS

#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

void testCreateAndDelete(bool* errorCode) {
    VertexValue value1 = { .key = 0};
    VertexValue value2 = { .key = 1};

    Graph* testGraph = createGraph(5, errorCode);
    addVertex(testGraph, value1, errorCode);
    addVertex(testGraph, value2, errorCode);
    deleteGraph(&testGraph, errorCode);
}

void testConnectVertices(bool* errorCode) {
    VertexValue value1 = { .key = 0};
    VertexValue value2 = { .key = 1};
    VertexValue value3 = { .key = 5};

    Graph* testGraph1 = createGraph(2, errorCode);
    addVertex(testGraph1, value1, errorCode);
    addVertex(testGraph1, value2, errorCode);
    addVertex(testGraph1, value3, errorCode);

    testGraph1 = connectVertices(testGraph1, 0, 5, errorCode);
    testGraph1 = connectVertices(testGraph1, 0, 1, errorCode);

    deleteGraph(&testGraph1, errorCode);
    if (*errorCode) {
        return;
    }
    VertexValue value4 = { .key = 5};
    VertexValue value5 = { .key = 1};
    VertexValue value6 = { .key = 0};

    Graph* testGraph2 = createGraph(3, errorCode);
    addVertex(testGraph2, value4, errorCode);
    addVertex(testGraph2, value5, errorCode);
    addVertex(testGraph2, value6, errorCode);

    testGraph2 = connectVertices(testGraph2, 0, 1, errorCode);
    testGraph2 = connectVertices(testGraph2, 0, 5, errorCode);
    deleteGraph(&testGraph2, errorCode);
}

bool areArraysEqual(bool array1[], bool array2[], int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }
    return true;
}

Graph* buildGraphUsingMatrix(const char* fileName, bool* errorCode) {
    FILE* file = fopen(fileName, "r");

    int graphSize = -1;
    fscanf(file, "%d\t", &graphSize);
    Graph* graph = createGraph(graphSize, errorCode);
    if (*errorCode) {
        fclose(file);
        return;
    }

    for (int key = 0; key < graphSize; ++key) {
        VertexValue value = { .key = key };
        addVertex(graph, value, errorCode);
        if (*errorCode) {
            fclose(file);
            deleteGraph(&graph, errorCode);
            return;
        }
    }

    int line = 0;
    int column = 0;
    int isEdge = false;
    while (fscanf(file, "%d\t", &isEdge) == 1) {
        if (isEdge) {
            graph = connectVertices(graph, column, line, errorCode);
            if (*errorCode) {
                fclose(file);
                deleteGraph(&graph, errorCode);
                return;
            }
        }
        column = (column + 1) % graphSize;
        if (column == 0) {
            ++line;
        }
    }
    fclose(file);
    return graph;
}

bool testTask3(void) {
    bool errorCode = false;
    bool resultTest1[6] = { false };
    resultTest1[0] = true;
    Graph* graph1 = buildGraphUsingMatrix("matrix.txt", &errorCode);
    if (errorCode) {
        deleteGraph(&graph1, errorCode);
        return false;
    }
    bool test1 = areArraysEqual(findGoodVertex(graph1, &errorCode), resultTest1, 6);
    if (errorCode) {
        deleteGraph(&graph1, errorCode);
        return false;
    }
    deleteGraph(&graph1, errorCode);

    bool resultTest2[1] = { true };
    Graph* graph2 = buildGraphUsingMatrix("test2.txt", &errorCode);
    if (errorCode) {
        deleteGraph(&graph2, errorCode);
        return false;
    }
    bool test2 = areArraysEqual(findGoodVertex(graph2, &errorCode), resultTest2, 1);
    if (errorCode) {
        deleteGraph(&graph2, errorCode);
        return false;
    }
    deleteGraph(&graph2, errorCode);

    return test1 && test2;
}

void testGraph(bool* errorCode) {
    testCreateAndDelete(errorCode);
    testConnectVertices(errorCode);
    errorCode = !testTask3();
}