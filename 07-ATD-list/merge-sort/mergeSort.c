#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "stringUtils.h"
#include "mergeSort.h"
#include "../listForMergeSort/list.h"

void merge(List* list, Position left, Position middle, Position right, SortingCriteria criteria, bool* errorCode) {
    List* result = createList(errorCode);
    if (*errorCode) {
        return;
    }
    Position i = first(result, errorCode);
    if (*errorCode) {
        deleteList(&result);
        return;
    }
    Position saveLeft = left;
    Position saveMiddle = middle;

    while (left != saveMiddle && middle != right) {
        char* leftValue = NULL;
        char* middleValue = NULL;
        if (criteria == name) {
            leftValue = getValue(left, errorCode).name;
            middleValue = getValue(middle, errorCode).name;
        }
        if (criteria == phone) {
            leftValue = getValue(left, errorCode).phone;
            middleValue = getValue(middle, errorCode).phone;
        }

        if (compareTwoString(leftValue, middleValue) < 0) {
            add(result, i, getValue(left, errorCode), errorCode);
            i = next(i, errorCode);
            left = next(left, errorCode);
            if (*errorCode) {
                deleteList(&result);
                return;
            }
        } else {
            add(result, i, getValue(middle, errorCode), errorCode);
            i = next(i, errorCode);
            middle = next(middle, errorCode);
            if (*errorCode) {
                deleteList(&result);
                return;
            }
        }
    }

    while (left != saveMiddle) {
        add(result, i, getValue(left, errorCode), errorCode);
        i = next(i, errorCode);
        left = next(left, errorCode);
        if (*errorCode) {
            deleteList(&result);
            return;
        }
    }

    while (middle != right) {
        add(result, i, getValue(middle, errorCode), errorCode);
        i = next(i, errorCode);
        middle = next(middle, errorCode);
        if (*errorCode) {
            deleteList(&result);
            return;
        }
    }

    i = next(first(result, errorCode), errorCode);
    if (*errorCode) {
        deleteList(&result);
        return;
    }
    left = saveLeft;
    for (Position j = left; j != NULL && i != NULL; j = next(j, errorCode)) {
        if (*errorCode) {
            deleteList(&result);
            return;
        }
        setValue(j, getValue(i, errorCode), errorCode);
        if (*errorCode) {
            deleteList(&result);
            return;
        }
        i = next(i, errorCode);
    }
    deleteList(&result);
}

Position calculateTheMiddle(List* list, Position left, Position right, bool* errorCode) {
    int middle = 0;
    Position i = left;
    while (i != NULL) {
        if (i == right) {
            break;
        }
        i = next(i, errorCode);
        ++middle;
    }
    i = left;

    int j = 0;
    while (j < (int)(middle / 2)) {
        i = next(i, errorCode);
        ++j;
    }
    return i;
}

void sortByMerging(List* list, Position left, Position right, SortingCriteria criteria, bool* errorCode) {
    if (next(left, errorCode) == right) {
        return;
    }
    Position saveRight = right;
    for (Position i = right; i != NULL; i = next(i, errorCode)) {
        if (*errorCode) {
            return;
        }
        if (i == left) {
            return;
        }
    }
    right = saveRight;

    Position middle = calculateTheMiddle(list, left, right, errorCode);
    if (*errorCode) {
        return;
    }
    sortByMerging(list, left, middle, criteria, errorCode);
    if (*errorCode) {
        return;
    }
    sortByMerging(list, middle, right, criteria, errorCode);
    if (*errorCode) {
        return;
    }
    merge(list, left, middle, right, criteria, errorCode);
}

void mergeSort(List* list, SortingCriteria criteria, bool* errorCode) {
    sortByMerging(list, next(first(list, errorCode), errorCode), NULL, criteria, errorCode);
}