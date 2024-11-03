#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "sortedList.h"
#include "../list/list.h"
#include "../list/testsForlist.h"
#include "testsForSortedList.h"

void printTheBackgroundInformation() {
    printf(
        "0 – выйти\n"
        "1 – добавить значение в сортированный список\n"
        "2 – удалить значение из списка\n"
        "3 – распечатать список\n");
}

void callTheFunction(int functionCode, bool* errorCode) {
    List* list = createList(errorCode);
    int listLength = 0;
    if (*errorCode) {
        deleteList(&list);
        return;
    }
    while (functionCode != 0) {
        if (functionCode == 1) {
            addItToTheSortedList(list, errorCode);
            if (*errorCode) {
                printf("При добавлении числа произошла ошибка\n");
                *errorCode = false;
            } else {
                ++listLength;
                printf("Число было успешно добавлено!\n");
            }
            sortTheList(list, listLength, errorCode);
            if (*errorCode) {
                printf("При сортировке произошла ошибка\n");
                *errorCode = false;
            }
        }
        if (functionCode == 2) {
            if (listLength == 0) {
                printf("Список пуст\n");
                functionCode = getTheFunctionCodeFromTheUser();
                continue;
            }
            removeANumberFromTheSortedList(list, listLength, errorCode);
            if (*errorCode) {
                printf("При удалении числа произошла ошибка\n");
                *errorCode = false;
            } else {
                printf("Число успешно удалено\n");
                --listLength;
            }
        }
        if (functionCode == 3) {
            printList(list, listLength, errorCode);
        }
        functionCode = getTheFunctionCodeFromTheUser();
    }
    deleteList(&list);
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getTheFunctionCodeFromTheUser(void) {
    int functionCode = -1;
    printTheBackgroundInformation();
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 3 || functionCode < 0 || scanfReturns != 1) {
        printf("Команда введена некорректно, попробуйте ещё раз\n");
        printTheBackgroundInformation();
        clearBuffer();
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

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

    callTheFunction(getTheFunctionCodeFromTheUser(), &errorCode);

    return errorCode;
}