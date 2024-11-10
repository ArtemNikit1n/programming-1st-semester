#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../list/list.h"
#include "mergeSort.h"

bool checkTheLexicographicOrder(List* list, bool errorCode) {
    for (Position i = first(list, errorCode); i != last(list, errorCode); i = next(i, errorCode)) {
        if (strcmp(i, next(i, errorCode)) > 0) {
            return false;
        }
    }
    return true;
}

bool testSortByMerging(bool* errorCode) {
    List* testList = createList(errorCode);
    add(testList, first(testList, errorCode), "Artem", errorCode);
    add(testList, first(testList, errorCode), "Nikitka", errorCode);
    add(testList, first(testList, errorCode), "Sashka", errorCode);
    add(testList, first(testList, errorCode), "Pashka", errorCode);

    sortByMerging(testList, first(testList, errorCode), last(testList, errorCode), errorCode);
    bool test1 = checkTheLexicographicOrder(testList, errorCode);
    return test1;
}

void runMergeSortingTests(bool* errorCode) {
    if (!testSortByMerging(errorCode)) {
        printf("Тест testSortByMerging не пройден\n");
        if (*errorCode) {
            printf("Ошибка в работе модуля\n");
        }
        *errorCode = true;
    }
}