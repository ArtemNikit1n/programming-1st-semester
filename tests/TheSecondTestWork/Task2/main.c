#include <stdbool.h>
#include <stdio.h>

#include "sortingArray.h"
#include "testsForTree.h"

bool isArraySorted(int array[], int arraySize) {
    for (int i = 0; i < arraySize - 1; ++i) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

bool* testSortingArray(bool *errorCode) {
    int testArray1[6] = {1, -2, 94, 94, 0, 5};
    sortByBuildingTree(testArray1, 6, errorCode);
    bool test1 = isArraySorted(testArray1, 6);

    sortByBuildingTree(NULL, 0, errorCode);

    int testArray2[3] = { 0, 0, 0 };
    sortByBuildingTree(testArray2, 3, errorCode);
    bool test2 = isArraySorted(testArray2, 3);

    int testArray3[1] = { 1000 };
    sortByBuildingTree(testArray3, 1, errorCode);
    bool test3 = isArraySorted(testArray3, 1);

    if (*errorCode) {
        return false;
    }
    return test1 && test2 && test3;
}

int main(void) {
    bool errorCode = false;
    runTheTreeTests(&errorCode);

    if (errorCode) {
        return errorCode;
    }

    if (!testSortingArray(&errorCode)) {
        errorCode = true;
        printf("Tests failed.");
        return errorCode;
    }
    printf("Tests passed.");

    return errorCode;
}