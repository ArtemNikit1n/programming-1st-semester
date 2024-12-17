#include "graph.h"

#include <stdlib.h>

testCreateAndDelete(bool* errorCode) {
    VertexValue value = { .stateNumber = 1, .isCapital = false };
    createGraph(createVertex(value, errorCode), errorCode);
}

void testGraph(bool* errorCode) {
    testCreateAndDelete(errorCode);
}