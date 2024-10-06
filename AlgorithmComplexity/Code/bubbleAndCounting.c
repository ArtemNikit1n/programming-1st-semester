#include <stdio.h>
#include <stdlib.h>
#include "headerFile.h"
#include "time.h"
#include <stdbool.h>

#define RANGE_OF_VALUES 100

void fillingAnArray(int array[], size_t arrayLength) {
    srand(time(NULL));
    for (int i = 0; i < arrayLength; ++i) {
        array[i] = rand() % 100;
    }
}

void bubbleSort(int array[], size_t arrayLength) {
    while (arrayLength > 1) {
        for (int i = 0; i < arrayLength - 1; ++i) {
            if (array[i] > array[i + 1]) {
                swap(&array[i + 1], &array[i]);
            }
        }
        --arrayLength;
    }
}

void countingSort(int array[], size_t arrayLength) {
    int j = 0;
    int arrayToCount[RANGE_OF_VALUES] = {0};
    for (int i = 0; i < arrayLength; ++i) {
        ++arrayToCount[array[i]];
    }
    for (int i = 0; i < RANGE_OF_VALUES; ++i) {
        if (arrayToCount[i] != 0) {
            while (arrayToCount[i] != 0) {
                array[j] = i;
                ++j;
                --arrayToCount[i];
            }
        }
    }
}

bool testBubbleSort() {
    int testArray[20] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    bubbleSort(testArray, 20);
    for (int i = 0; i < 19; ++i) {
        if (testArray[i] > testArray[i + 1]) {
            return false;
        }
    }
    return true;
}

bool testCountingSort() {
    int testArray[20] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    countingSort(testArray, 20);
    for (int i = 0; i < 19; ++i) {
        if (testArray[i] > testArray[i + 1]) {
            return false;
        }
    }
    return true;
}

bool testForCorrectMemoryAllocation(const int array[]) {
    return (array == NULL) ? true : false;
}

void bubbleAndCountingTask() {
    if (!testBubbleSort()) {
        printf("Bubble sort crash");
        return;
    }

    if (!testCountingSort()) {
        printf("Counting sort crash");
        return;
    }

    size_t arrayLength = 10000;
    int *arrayForBubble = (int *)malloc(arrayLength * sizeof(int));

    if (testForCorrectMemoryAllocation(arrayForBubble)) {
        printf("Memory allocation error\n");
        return;
    }

    fillingAnArray(arrayForBubble, arrayLength);

    clock_t startBubbleSort = clock();
    bubbleSort(arrayForBubble, arrayLength);
    clock_t endBubbleSort = clock();

    double timeSpentBubbleSorting = (double)(endBubbleSort - startBubbleSort) / CLOCKS_PER_SEC;

    free(arrayForBubble);
    int *arrayForCounting = malloc(arrayLength * sizeof(int));
    if (testForCorrectMemoryAllocation(arrayForCounting)) {
        printf("Memory allocation error\n");
        return;
    }

    fillingAnArray(arrayForCounting, arrayLength);

    clock_t startCountingSort = clock();
    countingSort(arrayForCounting, arrayLength);
    clock_t endCountingSort = clock();
    double timeSpentCountingSort = (double)(endCountingSort - startCountingSort) / CLOCKS_PER_SEC;

    free(arrayForCounting);
    printf("Time taken for bubble sorting: %f seconds", timeSpentBubbleSorting);
    printf("\nTime taken for counting sorting: %f seconds\n", timeSpentCountingSort);
}