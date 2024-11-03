#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

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
    add(list, 0, 32, &errorCode);
    add(list, 0, 543, &errorCode);
    printList(list);
    return errorCode;
}