#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "smartQSort.h"
#include "searchForTheMostFrequentElement.h"

void readAnArrayOfNumbersFromAFile(int memoryForNumbers[], int* arrayLength, bool* errorCode) {
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        *errorCode = true;
        return;
    }

    int i = 0;
    while (fscanf(file, "%d", &memoryForNumbers[i]) == 1) {
        i++;
    }
    fclose(file);
    *arrayLength = i;
}

bool testSmartQSort(bool *errorCode) {
    int testArray[21] = { 20, 19, 18, 117, 16, -15, 14, 13, 12, 11, -10, 9, 8, 7, 6, 5, 4, 3, 2, -1, 0 };
    smartQSort(testArray, 0, 20);
    for (int i = 0; i < 20; ++i) {
        if (testArray[i] > testArray[i + 1]) {
            printf("The testSmartQSort was not passed");
            *errorCode = true;
            return false;
        }
    }
    return true;
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

int main(void) {
    bool errorCode = false;

    if (!testSmartQSort(&errorCode)) {
        return errorCode;
    }

    if (!testFindTheMostCommonElement()) {
        printf("The test findTheMostCommonElement was not passed");
        return true;
    }

    int array[1000] = { 0 };
    int arrayLength = -1;
    readAnArrayOfNumbersFromAFile(array, &arrayLength, &errorCode);

    printf("Unsorted array from file: ");
    for (int i = 0; i < arrayLength; ++i) {
        printf("%d ", array[i]);
    }

    smartQSort(array, 0, arrayLength - 1);
    printf("\nSorted array: ");
    for (int i = 0; i < arrayLength; ++i) {
        printf("%d ", array[i]);
    }

    printf("\nThe most common element: %d", findTheMostCommonElement(array, arrayLength));

    return errorCode;
}