#include "graphsTests.h"
#include "graph.h"
#include "stacksTests.h"

#include <stdbool.h>
#include <stdio.h>

int main(void) {
    bool errorCode = false;
    runStackTest(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    testGraph(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    return errorCode;
}