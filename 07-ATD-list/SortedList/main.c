#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "sortedList.h"
#include "../list/list.h"
#include "../list/testsForlist.h"

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;
    runTheListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    List* list = createList(&errorCode);
    add(list, 0, 12, &errorCode);
    add(list, 1, -32, &errorCode);
    add(list, 2, 543, &errorCode);
    sortTheList(list, 3, &errorCode);
    printList(list, 3, &errorCode);
    printf("\n");
    add(list, 3, 0, &errorCode);
    sortTheList(list, 4, &errorCode);
    printList(list, 4, &errorCode);

    return errorCode;
}