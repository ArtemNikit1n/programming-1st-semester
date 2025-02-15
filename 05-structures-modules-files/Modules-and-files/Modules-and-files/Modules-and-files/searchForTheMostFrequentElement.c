#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "smartQSort.h"

int findTheMostCommonElement(int array[], int arrayLength) {
    smartQSort(array, 0, arrayLength - 1);
    int maximumLineLength = -1;
    int currentLengthOfTheString = 1;
    int theMostCommonElement = 0;
    for (int i = 0; i + 1 < arrayLength; ++i) {
        int j = i + 1;
        while (array[i] == array[j]) {
            ++currentLengthOfTheString;
            ++j;
        }
        if (max(currentLengthOfTheString, maximumLineLength) != maximumLineLength) {
            theMostCommonElement = array[i];
        }
        maximumLineLength = max(currentLengthOfTheString, maximumLineLength);
        currentLengthOfTheString = 1;
        i = j;
    }
    return theMostCommonElement;
}
