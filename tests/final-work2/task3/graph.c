#include "graph.h"
#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct Vertex {
    VertexValue value;
    int numberOfAdjacentVertices;
    bool visited;
    struct Vertex** adjacentVertices;
} Vertex;

struct Graph {
    int numberVertices;
    int numberVerticesVisited;
    bool** adjacencyMatrix;
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

int** expandMatrix(int** matrix, int currentSize, int desiredSize, bool* errorCode) {
    matrix = realloc(matrix, desiredSize * sizeof(int*));
    if (matrix == NULL) {
        *errorCode = true;
        return;
    }
    for (int i = currentSize; i < desiredSize; ++i) {
        matrix[i] = NULL;
    }

    for (int i = 0; i < desiredSize; ++i) {
        matrix[i] = realloc(matrix[i], desiredSize * sizeof(int));
        if (matrix[i] == NULL) {
            *errorCode = true;
            return;
        }
        if (i + 1 > currentSize) {
            memset(matrix[i], 0, desiredSize * sizeof(int));
        }
        else {
            for (int j = currentSize; j < desiredSize; ++j) {
                matrix[i][j] = 0;
            }
        }
    }
    return matrix;
}

void addVertex(Graph* graph, VertexValue value, bool* errorCode) {
    if (graph == NULL) {
        *errorCode = true;
        return;
    }
    if (graph->vertices == NULL) {
        graph->vertices = calloc(value.key, sizeof(Vertex*));
        if (graph->vertices == NULL) {
            *errorCode = true;
            return;
        }
    }

    if (value.key + 1 > graph->numberVertices) {
        graph->vertices = realloc(graph->vertices, (value.key + 1) * sizeof(Vertex*));
        if (graph->vertices == NULL) {
            *errorCode = true;
            return;
        }
        for (int i = graph->numberVertices; i < value.key + 1; ++i) {
            graph->vertices[i] = NULL;
        }

        graph->adjacencyMatrix = expandMatrix(graph->adjacencyMatrix, graph->numberVertices, value.key + 1, errorCode);
        if (*errorCode) {
            return;
        }
    }

    if (graph->vertices[value.key] != NULL) {
        *errorCode = true;
        return;
    }
    graph->vertices[value.key] = createVertex(value, errorCode);
    graph->numberVertices = max(graph->numberVertices, value.key + 1);
}

Vertex* addVertexToListOfAdjacentOnes(Vertex* vertex, Vertex* newVertex, bool* errorCode) {
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
        vertex->adjacentVertices = realloc(vertex->adjacentVertices, (vertex->numberOfAdjacentVertices + 1) * sizeof(Vertex*));
        if (vertex->adjacentVertices == NULL) {
            *errorCode = true;
            return;
        }

        vertex->adjacentVertices[vertex->numberOfAdjacentVertices] = newVertex;
        ++vertex->numberOfAdjacentVertices;
    }
    return vertex;
}

Graph* connectVertices(Graph* graph, int key1, int key2, bool* errorCode) {
    if (graph == NULL) {
        *errorCode = true;
        return;
    }

    if (key1 >= graph->numberVertices || key2 >= graph->numberVertices || key2 < 0 || key1 < 0) {
        *errorCode = true;
        return;
    }

    graph->adjacencyMatrix[key1][key2] = 1;

    graph->vertices[key1] = addVertexToListOfAdjacentOnes(graph->vertices[key1], graph->vertices[key2], errorCode);
    if (*errorCode) {
        return;
    }
    return graph;
}

void deleteMatrix(bool*** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        free((*matrix)[i]);
    }
    free(*matrix);
    *matrix = NULL;
}

bool** createMatrix(int size, bool* errorCode) {
    bool** matrix = calloc(1, size * sizeof(bool*));
    if (matrix == NULL) {
        *errorCode = true;
        return NULL;
    }

    for (int i = 0; i < size; ++i) {
        matrix[i] = calloc(1, size * sizeof(bool));
        if (matrix[i] == NULL) {
            deleteMatrix(&matrix, i + 1);
            *errorCode = true;
            return NULL;
        }
    }
    return matrix;
}

void deleteGraph(Graph** pointerToGraph, bool* errorCode) {
    if (*pointerToGraph == NULL) {
        *errorCode = true;
        return;
    }

    deleteMatrix(&(*pointerToGraph)->adjacencyMatrix, (*pointerToGraph)->numberVertices);
    for (int i = 0; i < (*pointerToGraph)->numberVertices; ++i) {
        if ((*pointerToGraph)->vertices[i] != NULL) {
            free((*pointerToGraph)->vertices[i]);
        }
    }
    free(*pointerToGraph);
    pointerToGraph = NULL;
}

Graph* createGraph(int initialSizeOfGraph, bool* errorCode) {
    Graph* graph = calloc(1, sizeof(Graph));
    if (graph == NULL) {
        *errorCode = true;
        return NULL;
    }

    graph->adjacencyMatrix = createMatrix(initialSizeOfGraph, errorCode);
    if (*errorCode) {
        deleteGraph(&graph, errorCode);
        return NULL;
    }

    if (initialSizeOfGraph <= 0) {
        deleteGraph(&graph, errorCode);
        *errorCode = true;
        return NULL;
    }
    Vertex** vertices = calloc(initialSizeOfGraph, sizeof(Vertex*));
    if (vertices == NULL) {
        deleteGraph(&graph, errorCode);
        *errorCode = true;
        return NULL;
    }
    graph->vertices = vertices;
    graph->numberVertices = initialSizeOfGraph;
    return graph;
}

void printMatrix(Graph* graph) {
    bool** matrix = graph->adjacencyMatrix;
    for (int i = 0; i < graph->numberVertices; ++i) {
        for (int j = 0; j < graph->numberVertices; ++j) {
            printf("%d\t", matrix[j][i]);
        }
        printf("\n");
    }
}

bool* findGoodVertex(Graph* graph, bool* errorCode) {
    bool* goodVertex = calloc(graph->numberVertices, sizeof(bool));
    if (goodVertex == NULL) {
        *errorCode = true;
        return NULL;
    }

    for (int i = 0; i < graph->numberVertices; ++i) {
        Vertex* startNode = graph->vertices[i];
        Stack* stack = createStack(errorCode);
        if (*errorCode) {
            free(goodVertex);
            return NULL;
        }
        push(stack, startNode->value.key, errorCode);
        if (*errorCode) {
            free(goodVertex);
            deleteStack(&stack, errorCode);
            return NULL;
        }

        graph->numberVerticesVisited = 0;

        while (!isEmpty(stack)) {
            int current = pop(stack, errorCode);
            if (*errorCode) {
                free(goodVertex);
                deleteStack(&stack, errorCode);
                return NULL;
            }

            if (graph->vertices[current]->visited) {
                continue;
            }

            graph->vertices[current]->visited = true;
            ++graph->numberVerticesVisited;

            for (int j = 0; j < graph->vertices[current]->numberOfAdjacentVertices; j++) {
                push(stack, graph->vertices[current]->adjacentVertices[j]->value.key, errorCode);
                if (*errorCode) {
                    free(goodVertex);
                    deleteStack(&stack, errorCode);
                    return NULL;
                }
            }
        }
        deleteStack(&stack, errorCode);
        if (graph->numberVerticesVisited == graph->numberVertices) {
            goodVertex[i] = true;
        }
    }
    return goodVertex;
}