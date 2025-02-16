#define _CRT_SECURE_NO_WARNINGS

#include "conversionToDecimal.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* convertToDecimal(const char* binaryNumber, bool* errorCode) {
    int lengthOfNumber = strlen(binaryNumber);
    if (lengthOfNumber >= 32) {
        *errorCode = true;
        return -1;
    }
    int decimal = 0;
    int coefficient = 1;

    for (int i = lengthOfNumber - 1; i >= 0; i--) {
        if (binaryNumber[i] == '1') {
            decimal += coefficient;
        }
        else if (binaryNumber[i] != '0') {
            *errorCode = true;
            return -1;
        }
        coefficient *= 2;
    }

    char* decimalString = malloc(10 * sizeof(char));
    if (decimalString == NULL) {
        return NULL;
    }
    sprintf(decimalString, "%d", decimal);
    return decimalString;
}