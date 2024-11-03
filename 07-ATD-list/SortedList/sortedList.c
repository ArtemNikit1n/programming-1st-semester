#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../list/list.h"

void swap(int* first, int* second) {
    if (*first == *second) {
        return;
    }
    *first ^= *second;
    *second ^= *first;
    *first ^= *second;
}

void sortByInsertionSort(int* array, int start, int stop) {
    for (int i = start + 1; i <= stop; ++i) {
        int indexSave = i;
        while (array[i] < array[i - 1] && start < i) {
            swap(&array[i], &array[i - 1]);
            --i;
        }
        i = indexSave;
    }
}

void sortTheList(List* list, int listLength, bool* errorCode) {
    int* arrayForSorting = calloc(listLength, sizeof(int));
    if (NULL == arrayForSorting) {
        *errorCode = true;
        return;
    }
    for (int i = 0; i < listLength; ++i) {
        int element = remove(list, 0, errorCode);
        arrayForSorting[i] = element;
        add(list, listLength - 1, element, errorCode);
        if (*errorCode) {
            return;
        }
    }
    sortByInsertionSort(arrayForSorting, 0, listLength - 1);
    for (int i = listLength - 1; i >= 0; --i) {
        remove(list, i, errorCode);
        add(list, i, arrayForSorting[i], errorCode);
        if (*errorCode) {
            return;
        }
    }
}

void printList(List* list, int listLength, bool *errorCode) {
    for (int i = 0; i < listLength; ++i) {
        int element = remove(list, 0, errorCode);
        printf("%d ", element);
        add(list, listLength - 1, element, errorCode);
        if (*errorCode) {
            printf("Произошла ошибка\n");
            return;
        }
    }
}