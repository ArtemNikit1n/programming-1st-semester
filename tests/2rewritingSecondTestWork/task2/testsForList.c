#include <stdbool.h>
#include <stdio.h>

#include "list.h"

void testListIsEmptyAndCreateList(bool* errorCode) {
    List* list = createList(errorCode);
    if (*errorCode) {
        deleteList(&list);
        return;
    }
    bool test = listIsEmpty(list, errorCode);
    deleteList(&list);
    if (!test) {
        *errorCode = true;
    }
}

void testAddAndRemove(bool* errorCode) {
    List* list = createList(errorCode);
    if (*errorCode) {
        deleteList(&list);
        return;
    }
    add(list, first(list, errorCode), 1, errorCode);
    add(list, next(first(list, errorCode), errorCode), 2, errorCode);
    add(list, next(next(first(list, errorCode), errorCode), errorCode), 3, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return;
    }

    bool test1 = removeListElement(list, next(first(list, errorCode), errorCode), errorCode) == 2;
    bool test2 = getValue(next(first(list, errorCode), errorCode), errorCode) == 1;
    bool test3 = removeListElement(list, first(list, errorCode), errorCode) == 1;
    removeListElement(list, first(list, errorCode), errorCode);
    if (*errorCode) {
        deleteList(&list);
        return;
    }
    bool test4 = listIsEmpty(list, errorCode);
    deleteList(&list);
    if (*errorCode) {
        return;
    }
    if (!(test1 && test2 && test3 && test4)) {
        *errorCode = true;
    }
}

void runTheListTests(bool* errorCode) {
    testListIsEmptyAndCreateList(errorCode);
    if (*errorCode) {
        return;
    }
    testAddAndRemove(errorCode);
}