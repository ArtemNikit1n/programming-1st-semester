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
    add(list, 0, 1, errorCode);
    add(list, 1, 2, errorCode);
    add(list, 2, 3, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    bool test1 = remove(list, 2, errorCode) == 3;
    bool test2 = remove(list, 1, errorCode) == 2;
    bool test3 = remove(list, 0, errorCode) == 1;

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

void runTheListTests(bool* errorCode) {
    if (!testListIsEmptyAndCreateList(errorCode)) {
        printf("Тест testListIsEmptyAndCreateList не пройден\n");
        if (*errorCode) {
            printf("Ошибка в работе модуля\n");
        }
        *errorCode = true;
    }
    if (!testAddAndRemove(errorCode)) {
        printf("Тест testAddAndRemove не пройден\n");
        if (*errorCode) {
            printf("Ошибка в работе модуля\n");
        }
        *errorCode = true;
    }
}