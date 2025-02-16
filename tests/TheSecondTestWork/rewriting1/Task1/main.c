#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void addNumberToArray(int** array, size_t* arraySize, int* numberOfAddedNumbers, const int number, bool* errorCode) {
    ++(*numberOfAddedNumbers);
    if (*numberOfAddedNumbers >= *arraySize) {
        *arraySize *= 2;
        int* newArray = realloc(*array, *arraySize * sizeof(int));
        if (newArray == NULL) {
            free(*array);
            *errorCode = true;
            return;
        }
        *array = newArray;
    }
    (*array)[*numberOfAddedNumbers - 1] = number;
}

int* task1(const char* fileName, const int a, const int b, bool* errorCode) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        *errorCode = true;
        return;
    }

    size_t capacityLessThanA = 2;
    int numberOfNumbersLessThanA = 0;
    int* numbersLessThanA = calloc(1, capacityLessThanA * sizeof(int));
    if (numbersLessThanA == NULL) {
        fclose(file);
        *errorCode = true;
        return;
    }

    size_t capacityBetweenAAndB = 2;
    int numberOfNumbersBetweenAAndB = 0;
    int* numbersBetweenAAndB = calloc(1, capacityBetweenAAndB * sizeof(int));
    if (numbersBetweenAAndB == NULL) {
        free(numberOfNumbersLessThanA);
        fclose(file);
        *errorCode = true;
        return;
    }

    size_t capacityGreaterThanB = 2;
    int numberOfNumbersGreaterThanB = 0;
    int* numbersGreaterThanB = calloc(1, capacityGreaterThanB * sizeof(int));
    if (numbersGreaterThanB == NULL) {
        free(numberOfNumbersLessThanA);
        free(numberOfNumbersBetweenAAndB);
        fclose(file);
        *errorCode = true;
        return;
    }
    size_t numberOfAllNumbers = 0;

    int currentNumber = -1;
    while (fscanf(file, "%d ", &currentNumber) == 1) {
        if (currentNumber < a) {
            addNumberToArray(&numbersLessThanA, &capacityLessThanA, &numberOfNumbersLessThanA, currentNumber, errorCode);
            if (*errorCode) {
                free(numberOfNumbersLessThanA);
                free(numberOfNumbersBetweenAAndB);
                free(numberOfNumbersGreaterThanB);
                fclose(file);
                return;
            }
        }
        if (currentNumber >= a && currentNumber <= b) {
            addNumberToArray(&numbersBetweenAAndB, &capacityBetweenAAndB, &numberOfNumbersBetweenAAndB, currentNumber, errorCode);
            if (*errorCode) {
                free(numberOfNumbersLessThanA);
                free(numberOfNumbersBetweenAAndB);
                free(numberOfNumbersGreaterThanB);
                fclose(file);
                return;
            }
        }
        if (currentNumber > b) {
            addNumberToArray(&numbersGreaterThanB, &capacityGreaterThanB, &numberOfNumbersGreaterThanB, currentNumber, errorCode);
            if (*errorCode) {
                free(numberOfNumbersLessThanA);
                free(numberOfNumbersBetweenAAndB);
                free(numberOfNumbersGreaterThanB);
                fclose(file);
                return;
            }
        }
    }

    //int* outputArray = calloc(1, numberOfAllNumbers * sizeof(int));
    //for (int i = 0; i < numberOfNumbersLessThanA; ++i) {
    //    outputArray[i] = numbersLessThanA[i];
    //}
    //for (int i = numberOfNumbersLessThanA; i < numberOfNumbersBetweenAAndB + numberOfNumbersLessThanA; ++i) {
    //    outputArray[i] =
    //}
    //for (int i = numberOfNumbersBetweenAAndB + numberOfNumbersLessThanA; i < numberOfAllNumbers; ++i) {
    //    outputArray[i] =
    //}

    free(numberOfNumbersLessThanA);
    free(numberOfNumbersBetweenAAndB);
    free(numberOfNumbersGreaterThanB);
    fclose(file);
}

void testTask1(bool* errorCode) {
    task1("f.txt", 5, 10, errorCode);
}

int main(void) {
    bool errorCode = false;
    testTask1(&errorCode);
    if (errorCode) {
        printf("Test FAILED\n");
        return errorCode;
    }
    else {
        printf("Test PASSED\n");
    }
    return errorCode;
}