#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../list/list.h"

void sortListByInserts(List* list, bool* errorCode) {
    if (listIsEmpty(list, errorCode)) {
        return;
    }

    Position sortedEnd = first(list);
    Position unsortedStart = next(sortedEnd, errorCode);
    while (unsortedStart != NULL) {
        Value valueToInsert = getValue(unsortedStart, errorCode);

        Position insertPosition = first(list);
        while (insertPosition != unsortedStart) {
            Value currentValue = getValue(next(insertPosition, errorCode), errorCode);
            if (currentValue > valueToInsert) {
                break;
            }
            insertPosition = next(insertPosition, errorCode);
        }

        if (insertPosition != unsortedStart) {
            removeListElement(list, sortedEnd, errorCode);
            add(list, insertPosition, valueToInsert, errorCode);
        }
        else {
            sortedEnd = unsortedStart;
        }
        unsortedStart = next(sortedEnd, errorCode);
    }
}

void printList(const List* list, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return;
    }
    if (errorCode == NULL) {
        return;
    }
    for (Position i = first(list); i != last(list, errorCode); i = next(i, errorCode)) {
        printf("%d ", getValue(next(i, errorCode), errorCode));
        if (*errorCode) {
            printf("Ошибка. Невозможно вывести список.\n");
            return;
        }
    }
    printf("\n");
}

void addItToSortedList(List* list, int valueToAdd, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return;
    }
    if (errorCode == NULL) {
        return;
    }
    add(list, last(list, errorCode), valueToAdd, errorCode);
    sortListByInserts(list, errorCode);
}

void deleteFromSortedList(List* list, int valueToDelete, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return;
    }
    if (errorCode == NULL) {
        return;
    }
    for (Position i = first(list); i != last(list, errorCode); i = next(i, errorCode)) {
        if (valueToDelete == getValue(next(i, errorCode), errorCode)) {
            removeListElement(list, i, errorCode);
            return;
        }
        if (*errorCode) {
            return;
        }
    }
}