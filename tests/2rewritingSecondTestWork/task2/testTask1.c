#include "list.h"

#include <stdlib.h>

bool onlyOddIndexes(List* list, bool* errorCode) {
    for (Position i = next(first(list, errorCode), errorCode); i != NULL; i = next(i, errorCode)) {
        if (getValue(i, errorCode) % 2 != 1) {
            return false;
        }
    }
    return true;
}

void deleteOddIndexes(List* list, bool* errorCode) {
    if (list == NULL) {
        return;
    }

    int index = 0;
    Position i = first(list, errorCode);
    while (i != NULL) {
        if (list == NULL) {
            *errorCode = true;
            return;
        }
        if (index % 2 == 1) {
            if (next(i, errorCode) == NULL) {
                return;
            }
            removeListElement(list, i, errorCode);
            ++index;
            continue;
        }
        ++index;
        i = next(i, errorCode);
    }
}

void testTask1(bool* errorCode) {
    List* evenNumberOfElements = createList(errorCode);
    if (*errorCode) {
        return;
    }
    Position first1 = first(evenNumberOfElements, errorCode);
    if (*errorCode) {
        deleteList(&evenNumberOfElements);
        return;
    }
    for (int i = 1; i < 6; ++i) {
        add(evenNumberOfElements, first1, i, errorCode);
        if (*errorCode) {
            deleteList(&evenNumberOfElements);
            return;
        }
        first1 = next(first1, errorCode);
        if (*errorCode) {
            deleteList(&evenNumberOfElements);
            return;
        }
    }
    deleteOddIndexes(evenNumberOfElements, errorCode);
    if (!onlyOddIndexes(evenNumberOfElements, errorCode)) {
        deleteList(&evenNumberOfElements);
        *errorCode = true;
        return;
    }
    deleteList(&evenNumberOfElements);

    List* nonevenNumberOfElements = createList(errorCode);
    if (*errorCode) {
        return;
    }
    Position first2 = first(nonevenNumberOfElements, errorCode);
    if (*errorCode) {
        deleteList(&nonevenNumberOfElements);
        return;
    }
    for (int i = 1; i < 101; ++i) {
        add(nonevenNumberOfElements, first2, i, errorCode);
        if (*errorCode) {
            deleteList(&nonevenNumberOfElements);
            return;
        }
        first2 = next(first2, errorCode);
        if (*errorCode) {
            deleteList(&nonevenNumberOfElements);
            return;
        }
    }
    deleteOddIndexes(nonevenNumberOfElements, errorCode);
    if (!onlyOddIndexes(nonevenNumberOfElements, errorCode)) {
        deleteList(&nonevenNumberOfElements);
        *errorCode = true;
        return;
    }
    deleteList(&nonevenNumberOfElements);

    List* emptyList = createList(errorCode);
    deleteOddIndexes(nonevenNumberOfElements, errorCode);
    deleteList(emptyList);
}