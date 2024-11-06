#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "../TheCyclicList/theCyclicList.h"
#include "../TheCyclicList/testsForList.h"

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getANumberFromTheUser(void) {
    int number = -1;
    int scanfReturns = scanf("%d", &number);
    while (scanfReturns != 1) {
        printf("Ошибка ввода, попробуйте ещё раз\n");
        clearBuffer();
        scanfReturns = scanf("%d", &number);
    }
    clearBuffer();
    return number;
}

//int calculateTheLastRemainingPosition(const int theNumberOfWars, int theDeadOfWar, bool* errorCode) {
//    List* list = createList(errorCode);
//    for (int i = 1; i <= theNumberOfWars; ++i) {
//        add(list, i - 1, i, errorCode);
//        if (*errorCode) {
//            deleteList(&list);
//            return -1;
//        }
//    }
//
//    int theLastWarriorKilled = -1;
//    while (!listIsEmpty(list, errorCode)) {
//        theLastWarriorKilled = removeListElement(list, theDeadOfWar - 1, errorCode);
//        if (*errorCode) {
//            deleteList(&list);
//            return -1;
//        }
//        theDeadOfWar = (theDeadOfWar + 2) % 41;
//    }
//    return theLastWarriorKilled;
//}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;
    //runTheListTests(&errorCode);
    //if (errorCode) {
    //    return errorCode;
    //}
    //printf("Введите n (количество войнов):\n");
    //int theNumberOfWars = 41;
    //printf("Каждые два война убивают каждого m-го. Введите m:\n");
    //int theDeadOfWar = 3;
    //int theSurvivor = calculateTheLastRemainingPosition(theNumberOfWars, theDeadOfWar, &errorCode);
    //if (errorCode) {
    //    printf("Произошла ошибка\n");
    //    return errorCode;
    //}
    //printf("%d (Человек под этим номером останется в живых)\n", theSurvivor);

    List* list = createList(&errorCode);
    add(list, first(list, &errorCode), 3, &errorCode);
    add(list, first(list, &errorCode), 2, &errorCode);
    add(list, first(list, &errorCode), 1, &errorCode);
    add(list, next(first(list, &errorCode), &errorCode), 4, &errorCode);
    add(list, last(list, &errorCode), 5, &errorCode);

    int value = getValue(first(list, &errorCode), &errorCode);
    removeListElement(list, next(first(list, &errorCode), &errorCode), &errorCode);
    deleteList(&list);
    return errorCode;
}