#include <stdlib.h>
#include <stdbool.h>

#include "mergeSort.h"
#include "../list/list.h"

void merge(List* list, Position left, Position mid, Position right, bool* errorCode) {
    return;
}

Position calculateTheMiddle(List* list, Position left, Position right, bool* errorCode) {
    int middle = 0;
    Position i = left;
    while (i != last(list, errorCode)) {
        i = next(i, errorCode);
        if (i == right) {
            break;
        }
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

void sortByMerging(List* list, Position left, Position right, bool* errorCode) {
    if (next(left, errorCode) >= right) {
        return;
    }
    Position middle = calculateTheMiddle(list, left, right, errorCode);
    sortByMerging(list, left, middle, errorCode);
    sortByMerging(list, middle, right, errorCode);
    merge(list, left, middle, right, errorCode);
}