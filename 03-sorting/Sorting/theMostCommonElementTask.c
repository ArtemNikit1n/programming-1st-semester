#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "headerFile.h"

int findTheMostCommonElement(int array[], int arrayLength) {
    smartQSort(array, 0, arrayLength - 1);
    int maximumLineLength = -1;
    int currentLengthOfTheString = 1;
    int theMostCommonElement = -1;
    for (int i = 0; i + 1 < arrayLength; ++i) {
        int j = i + 1;
        while (array[i] == array[j] && j < arrayLength) {
            ++currentLengthOfTheString;
            ++j;
        }
        if (currentLengthOfTheString > maximumLineLength) {
            theMostCommonElement = array[i];
        }
        maximumLineLength = max(currentLengthOfTheString, maximumLineLength);
        currentLengthOfTheString = 1;
        i = j;
    }
    return theMostCommonElement;
}

bool testFindTheMostCommonElement() {
    int testArray1[15] = { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5 };
    int testArray2[5] = { 0, 0, 0, 0, 0, };
    int testArray3[10] = { -1, -2, 2, -3, -3, -3, -4, 4, 1000000, 4 };
    bool test1 = findTheMostCommonElement(testArray1, 15) == 5;
    bool test2 = findTheMostCommonElement(testArray2, 5) == 0;
    bool test3 = findTheMostCommonElement(testArray3, 10) == -3;

    return test1 && test2 && test3;
}

int getIntValueFromUser(void) {
    int value = -1;
    int scanfReturns = scanf("%d", &value);
    while (scanfReturns != 1) {
        printf("Input error\n");
        while (getchar() != '\n');
        scanfReturns = scanf("%d", &value);
    }
    return value;
}

bool theMostCommonElementTask(void) {
    bool errorCode = false;

    int array[1000] = { 0 };
    if (!testFindTheMostCommonElement()) {
        printf("Test failed");
        return true;
    }

    printf("Enter the array size (<1000):\n");

    int arrayLength = getIntValueFromUser();
    if (arrayLength > 1000 || arrayLength < 1) {
        printf("Invalid array value");
        return true;
    }

    srand(time(NULL));
    generateRandomArrays(array, arrayLength);
    printf("Unsorted array: ");
    for (int i = 0; i < arrayLength; ++i) {
        printf("%d ", array[i]);
    }

    printf("\nThe most common element: %d", findTheMostCommonElement(array, arrayLength));

    printf("\nSorted array: ");
    for (int i = 0; i < arrayLength; i++) {
        printf("%d ", array[i]);
    }
    return errorCode;
}