#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../list/list.h"
#include "mergeSort.h"

bool checkTheLexicographicOrder(List* list, bool* errorCode) {
    for (Position i = next(first(list, errorCode), errorCode); i != last(list, errorCode); i = next(i, errorCode)) {
        Position j = next(i, errorCode);
        if (strcmp(getValue(i, errorCode), getValue(i, errorCode)) > 0) {
            return false;
        }
        if (*errorCode) {
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

    sortByMerging(testList, first(testList, errorCode), NULL, errorCode);
    bool test1 = checkTheLexicographicOrder(testList, errorCode);
    deleteList(&testList);
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