#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../listForMergeSort/list.h"
#include "mergeSort.h"
#include "stringUtils.h"

bool checkTheLexicographicOrder(List* list, SortingCriteria criteria, bool* errorCode) {
    for (Position i = next(first(list, errorCode), errorCode); i != last(list, errorCode); i = next(i, errorCode)) {
        Position j = next(i, errorCode);

        char* iValue = NULL;
        char* jValue = NULL;
        if (criteria == name) {
            iValue = getValue(i, errorCode).name;
            jValue = getValue(j, errorCode).name;
        }
        if (criteria == phone) {
            iValue = getValue(i, errorCode).phone;
            jValue = getValue(j, errorCode).phone;
        }
        if (compareTwoString(iValue, jValue) > 0) {
            return false;
        }
        if (*errorCode) {
            return false;
        }
    }
    return true;
}

bool testSortByMerging(bool* errorCode) {
    List* testList = createList(errorCode);
    if (*errorCode) {
        return false;
    }
    NameAndPhone testStruct = { .name = "Artem", .phone = "89123599486" };
    add(testList, first(testList, errorCode), testStruct, errorCode);
    if (*errorCode) {
        deleteList(&testList);
        return false;
    }
    testStruct.name = "Nikitka";
    testStruct.phone = "89123219486";
    add(testList, first(testList, errorCode), testStruct, errorCode);
    if (*errorCode) {
        deleteList(&testList);
        return false;
    }
    testStruct.name = '\0';
    testStruct.phone = "-023-12-";
    add(testList, first(testList, errorCode), testStruct, errorCode);
    if (*errorCode) {
        deleteList(&testList);
        return false;
    }
    testStruct.name = "Pashka";
    testStruct.phone = '\0';
    add(testList, first(testList, errorCode), testStruct, errorCode);
    if (*errorCode) {
        deleteList(&testList);
        return false;
    }

    mergeSort(testList, phone, errorCode);
    if (*errorCode) {
        deleteList(&testList);
        return false;
    }
    bool test1 = checkTheLexicographicOrder(testList, phone, errorCode);
    mergeSort(testList, name, errorCode);
    if (*errorCode) {
        deleteList(&testList);
        return false;
    }
    bool test2 = checkTheLexicographicOrder(testList, name, errorCode);
    deleteList(&testList);
    return test1 && test2;
}

void runMergeSortingTests(bool* errorCode) {
    if (!testSortByMerging(errorCode)) {
        printf("Тест testSortByMerging не пройден\n");
        *errorCode = true;
    }
}