#define _CRT_SECURE_NO_WARNINGS

#include "graphsTests.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    bool errorCode = false;
    testGraph(&errorCode);
    return errorCode;
}