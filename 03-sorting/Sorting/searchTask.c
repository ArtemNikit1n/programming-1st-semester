#include "headerFile.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool isNumberInArray(int desiredValue, int array[], size_t arrayLength) {
    if (array == NULL) {
        return false;
    }
    smartQSort(array, 0, arrayLength - 1);

    int start = 0;
    int stop = arrayLength - 1;

    while (true) {
        if (start > stop) {
            return false;
        }
        size_t averageIndex = (size_t)((start + stop) / 2);
        if (array[averageIndex] == desiredValue) {
            return true;
        }
        else if (array[averageIndex] < desiredValue) {
            start = averageIndex + 1;
        }
        else {
            stop = averageIndex - 1;
        }
    }
}

bool* search(int searchArea[], size_t searchAreaLength, int desiredNumbersArray[], size_t desiredNumbersArrayLength, bool* errorCode) {
    bool* isNumberInSearchArea = calloc(desiredNumbersArrayLength, sizeof(bool));
    if (isNumberInSearchArea == NULL) {
        *errorCode = true;
        return NULL;
    }

    if (searchArea == NULL) {
        return isNumberInSearchArea;
    }
    if (desiredNumbersArray == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < desiredNumbersArrayLength; ++i) {
        if (isNumberInArray(desiredNumbersArray[i], searchArea, searchAreaLength)) {
            isNumberInSearchArea[i] = true;
        }
    }
    return isNumberInSearchArea;
}

bool areBitScalesEqual(bool firstBitScale[], bool secondBitScale[], size_t bitScaleSize) {
    for (size_t i = 0; i < bitScaleSize; ++i) {
        if (firstBitScale[i] != secondBitScale[i]) {
            return false;
        }
    }
    return true;
}

void testSearch(bool* errorCode) {
    int testSearchArea[9] = { 1, 2, 3, 3, 3, 4, 5, 5, 6 };
    int test1DesiredNumbersArray[2] = { 1, 6 };
    bool* test1Result = search(testSearchArea, 9, test1DesiredNumbersArray, 2, errorCode);
    bool expectedResultOfFirstTest[2] = {true, true};
    if (*errorCode) {
        free(test1Result);
        return;
    }
    if (!areBitScalesEqual(test1Result, expectedResultOfFirstTest, 2)) {
        free(test1Result);
        *errorCode = true;
        return;
    }

    int test2DesiredNumbersArray[3] = { 4, 10, 5 };
    bool expectedResultOfSecondTest[3] = { true, false, true };
    bool* test2Result = search(testSearchArea, 9, test2DesiredNumbersArray, 3, errorCode);
    if (*errorCode) {
        free(test1Result);
        free(test2Result);
        return;
    }
    if (!areBitScalesEqual(test2Result, expectedResultOfSecondTest, 3)) {
        free(test1Result);
        free(test2Result);
        *errorCode = true;
        return;
    }
    free(test1Result);
    free(test2Result);
}

bool testIsNumberInArray(void) {
    int testArray[9] = { 1, 2, 3, -3, 3, -4, 5, 5, 0 };
    if (!isNumberInArray(3, testArray, 9)) {
        return false;
    }
    if (!isNumberInArray(-3, testArray, 9)) {
        return false;
    }
    if (isNumberInArray(12, testArray, 9)) {
        return false;
    }
    if (isNumberInArray(-32, testArray, 9)) {
        return false;
    }
    return true;
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

bool searchTask(void) {
    int searchArea[1000] = { 0 };
    int desiredNumbersArray[1000] = { 0 };
    bool errorCode = false;

    if (!testIsNumberInArray()) {
        printf("Test failed\n");
        return true;
    }

    testSearch(&errorCode);
    if (errorCode){
        printf("Test failed\n");
        return errorCode;
    }

    printf("Enter a total number of numbers less than 1000:\n");
    int searchAreaLength = getIntValueFromUser();
    if (searchAreaLength <= 0 && searchAreaLength >= 1000) {
        printf("Input error");
        return true;
    }

    printf("Enter the number of numbers less than 1000 you want to find:\n");
    int desiredNumbers = getIntValueFromUser();
    if (desiredNumbers <= 0 && desiredNumbers >= 1000) {
        printf("Input error");
        return true;
    }

    srand(time(NULL));
    generateRandomArrays(searchArea, searchAreaLength);
    generateRandomArrays(desiredNumbersArray, desiredNumbers);
    bool* isNumberInSearchArea = search(searchArea, searchAreaLength, desiredNumbersArray, desiredNumbers, &errorCode);
    if (errorCode) {
        free(isNumberInSearchArea);
        printf("Error.");
        return true;
    }

    printf("\nSorted search area: ");
    for (int i = 0; i < searchAreaLength; ++i) {
        printf("%d ", searchArea[i]);
    }
    printf("\nArray of the desired numbers: ");
    for (int i = 0; i < desiredNumbers; ++i) {
        printf("%d ", desiredNumbersArray[i]);
    }
    printf("\nThe numbers found: ");
    for (int i = 0; i < desiredNumbers; ++i) {
        if (isNumberInSearchArea[i]) {
            printf("%d ", desiredNumbersArray[i]);
        }
    }

    free(isNumberInSearchArea);
    return false;
}