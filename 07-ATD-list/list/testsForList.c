#include <stdbool.h>
#include <stdio.h>

#include "../list/list.h"

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
    const char* testString1 = "abcd";
    const char* testString2 = "\0";
    const char* testString3 = "-43243432434";

    add(list, first(list, errorCode), testString1, errorCode);
    add(list, next(first(list, errorCode), errorCode), testString2, errorCode);
    add(list, next(next(first(list, errorCode), errorCode), errorCode), testString3, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }

    bool test1 = removeListElement(list, next(first(list, errorCode), errorCode), errorCode) == testString2;
    bool test2 = getValue(next(first(list, errorCode), errorCode), errorCode) == testString1;
    bool test3 = removeListElement(list, first(list, errorCode), errorCode) == testString1;
    removeListElement(list, first(list, errorCode), errorCode);
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
        printf("Тест testListIsEmptyAndCreateList не пройден\n");
        if (*errorCode) {
            printf("Ошибка в работе модуля\n");
        }
        *errorCode = true;
        return false;
    }
    if (!testAddAndRemove(errorCode)) {
        printf("Тест testAddAndRemove не пройден\n");
        if (*errorCode) {
            printf("Ошибка в работе модуля\n");
        }
        *errorCode = true;
        return false;
    }
}