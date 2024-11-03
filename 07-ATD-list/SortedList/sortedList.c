#include <stdbool.h>
#include <stdio.h>

#include "../list/list.h"

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