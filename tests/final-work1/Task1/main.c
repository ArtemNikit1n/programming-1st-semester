#include "conversionToDecimal.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void testTask1(bool* errorCode) {
    if (0 != strcmp("0", convertToDecimal("0", errorCode))) {
        *errorCode = true;
    }
    if (0 != strcmp("1", convertToDecimal("1", errorCode))) {
        *errorCode = true;
    }
    if (0 != strcmp("20", convertToDecimal("10100", errorCode))) {
        *errorCode = true;
    }
    if (0 != strcmp("2147483647", convertToDecimal("1111111111111111111111111111111", errorCode))) {
        *errorCode = true;
    }
    if (0 != strcmp("134103039", convertToDecimal("111111111100011111111111111", errorCode))) {
        *errorCode = true;
    }
}

int main(void) {
    bool errorCode = false;

    testTask1(&errorCode);
    if (errorCode) {
        printf("Tests failed");
    }
    else {
        printf("Tests passed");
    }

    return errorCode;
}