#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "sortedList.h"
#include "../list/list.h"
#include "../list/testsForlist.h"
#include "testsForSortedList.h"

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;
    runTheListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    runTheSortedListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    List* list = createList(&errorCode);
    deleteList(&list);

    return errorCode;
}