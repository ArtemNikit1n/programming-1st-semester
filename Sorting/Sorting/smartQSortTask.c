#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void swap(int* first, int* second) {
    if (*first == *second) {
        return;
    }
    int tmp = *first;
    *first = *second;
    *second = tmp;
}

void insertionsort(int array[], int startIndex, int endIndex) {
    for (int i = startIndex + 1; i <= endIndex; ++i) {
        int j = i;
        while(array[j] < array[j - 1] && startIndex < j) {
            swap(&array[j], &array[j - 1]);
            --j;
        }
    }
}

int halfQSort(int array[], int startIndex, int endIndex) {
    int randomIndex = startIndex + (rand() % (endIndex - startIndex + 1));
    swap(&array[startIndex], &array[randomIndex]);

    int supportingElement = array[startIndex];
    int leftPart = startIndex + 1;

    for (int rightPart = startIndex + 1; rightPart <= endIndex; ++rightPart) {
        if (array[rightPart] < supportingElement) {
            swap(&array[leftPart], &array[rightPart]);
            ++leftPart;
        }
    }
    swap(&array[startIndex], &array[leftPart - 1]);
    return leftPart - 1;
}

void smartQSort(int array[], int start, int stop) {
    if (start >= stop) {
        return;
    }
    if (stop - start > 0) {
        int supportingIndex = halfQSort(array, start, stop);

        if (supportingIndex - 1 > start) {
            smartQSort(array, start, supportingIndex - 1);
        }
        if (supportingIndex + 1 < stop) {
            smartQSort(array, supportingIndex + 1, stop);
        }
    }
    if (stop - start <= 10) {
        insertionSort(array, start, stop);
    }
}

void generateRandomArrays(int randomArray[], int arrayLength) {
    for (int i = 0; i < arrayLength; ++i) {
        randomArray[i] = rand() % 100;
        if (i % 5 == 0) {
            randomArray[i] = -randomArray[i];
        }
    }
}

bool isArraySorted(int array[], int arrraySize) {
    for (int i = 0; i < arrraySize - 1; ++i) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

bool testSmartQSort() {
    int testArray1[] = { 0 };
    smartQSort(testArray1, 0, 0);
    bool test1 = testArray1[0] == 0;

    int testArray2[21] = { -20, 19, 18, 17, 16, 15, 14, 13, -12, 11, 10, 9, 8, 7, 6, 5, -4, 3, 2, 1, 0};
    smartQSort(testArray2, 0, 20);
    bool test2 = isArraySorted(testArray2, 21);

    return test2 && test1;
}

bool smartQSortTask(void) {
    char* endptrArrayLength = NULL;
    char strArrayLength[6] = { 0 };

    int array[1000] = { 0 };
    int arrayLength = -1;
    bool errorCode = false;

    if (!testSmartQSort()) {
        errorCode = true;
        printf("Test failed");
        return errorCode;
    }

    printf("Enter the array size:\n");
    scanf("%s", strArrayLength);
    arrayLength = (int)strtol(strArrayLength, &endptrArrayLength, 10);

    if (arrayLength > 1000 || arrayLength < 1 || *endptrArrayLength != '\0') {
        printf("Invalid array value");
        errorCode = true;
        return errorCode;
    }

    srand(time(NULL));
    generateRandomArrays(array, arrayLength);
    printf("Unsorted array: ");
    for (int i = 0; i < arrayLength; ++i) {
        printf("%d ", array[i]);
    }

    smartQSort(array, 0, arrayLength - 1);
    printf("\nSorted array: ");
    for (int i = 0; i < arrayLength; ++i) {
        printf("%d ", array[i]);
    }
    return errorCode;
}