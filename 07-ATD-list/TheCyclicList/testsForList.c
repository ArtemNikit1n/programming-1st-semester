#include <stdbool.h>
#include <stdio.h>

#include "../TheCyclicList/theCyclicList.h"

bool testListIsEmptyAndCreateList(bool* errorCode) {
    List* list = createList(errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    bool test = listIsEmpty(list, errorCode);
    deleteList(&list);
    return test;
}

bool testAddAndRemove(bool* errorCode) {
    List* list = createList(errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }

    add(list, first(list, errorCode), 1, errorCode);
    add(list, next(first(list, errorCode), errorCode), 2, errorCode);
    add(list, last(list, errorCode), 3, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }


    bool test1 = removeListElement(list, last(list, errorCode), errorCode) == 1;
    bool test2 = getValue(first(list, errorCode), errorCode) == 2;
    bool test3 = removeListElement(list, first(list, errorCode), errorCode) == 3;
    removeListElement(list, next(first(list, errorCode), errorCode), errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    bool test4 = listIsEmpty(list, errorCode);
    deleteList(&list);
    if (*errorCode) {
        return false;
    }
    return test1 && test2 && test3 && test4;
}

bool runTheListTests(bool* errorCode) {
    if (!testListIsEmptyAndCreateList(errorCode)) {
        printf("���� testListIsEmptyAndCreateList �� �������\n");
        *errorCode = true;
        return false;
    }
    if (!testAddAndRemove(errorCode)) {
        printf("���� testAddAndRemove �� �������\n");
        *errorCode = true;
        return false;
    }
}