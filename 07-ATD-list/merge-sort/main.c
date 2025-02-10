#define _CRT_SECURE_NO_WARNINGS

#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 20

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include "stringUtils.h"
#include "mergeSort.h"
#include "../listForMergeSort/list.h"
#include "../listForMergeSort/testsForList.h"

void printTheBackgroundInformation(void) {
    printf(
        "0 � �����\n"
        "1 � ������������� �� ������ ��������\n"
        "2 � ������������� �� �����\n"
        "3 � ����������� ������ �� �����\n"
    );
}

void printList(const List* list, bool* errorCode) {
    for (Position i = first(list, errorCode); i != last(list, errorCode); i = next(i, errorCode)) {
        printf("%s - %s\n", getValue(next(i, errorCode), errorCode).name, getValue(next(i, errorCode), errorCode).phone);
        if (*errorCode) {
            printf("������. ����� ����� ��������� ����������.\n");
            return;
        }
    }
    printf("\n");
}

void readFromTheFile(List* records, const char* filename, bool* errorCode) {
    FILE* file = fopen(filename, "r");
    if (file == NULL || records == NULL) {
        *errorCode = true;
        return;
    }

    Position i = first(records, errorCode);
    int scanfResult = 2;
    while (scanfResult == 2) {
        char* name = calloc(1, sizeof(char) * MAX_NAME_LENGTH);
        if (name == NULL) {
            *errorCode = true;
            return;
        }
        char* phone = calloc(1, sizeof(char) * MAX_PHONE_LENGTH);
        if (phone == NULL) {
            free(name);
            *errorCode = true;
            return;
        }
        scanfResult = fscanf(file, "%s - %s\n", name, phone);
        if (scanfResult != 2) {
            break;
        }

        NameAndPhone currentData = { .name = name, .phone = phone };
        add(records, i, currentData, errorCode);
        if (*errorCode) {
            free(name);
            free(phone);
            return;
        }
        i = next(i, errorCode);
        if (*errorCode) {
            free(name);
            free(phone);
            return;
        }
    }
    fclose(file);
}

void callTheFunction(int functionCode, bool* errorCode) {
    List* records = createList(errorCode);
    if (*errorCode) {
        printf("������ ��������� ������");
        return;
    }
    readFromTheFile(records, "phoneDatabase.txt", errorCode);
    if (*errorCode) {
        deleteList(&records);
        printf("������ ��� ������ �� �����");
        return;
    }
    while (functionCode != 0) {
        if (functionCode == 1) {
            mergeSort(records, phone, errorCode);
            if (*errorCode) {
                deleteList(&records);
                printf("��������� ������, ���������� �����\n");
                return;
            }
            printf("������ ��������� ���� ������� �������������!\n");
        }
        if (functionCode == 2) {
            mergeSort(records, name, errorCode);
            if (*errorCode) {
                deleteList(&records);
                printf("��������� ������, ���������� �����\n");
                return;
            }
            printf("����� ��������� ���� ������� �������������!\n");
        }
        if (functionCode == 3) {
            printf("���� ��������:\n");
            printList(records, errorCode);
        }
        functionCode = getTheFunctionCodeFromTheUser();
    }
    deleteList(&records);
}

int getTheFunctionCodeFromTheUser(void) {
    int functionCode = -1;
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 3 || functionCode < 0 || scanfReturns != 1) {
        printf("����� ������� ����� �����������, ���������� ��� ���\n");
        printTheBackgroundInformation();
        while (getchar() != '\n');
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
    runMergeSortingTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    testAllUtilitiesForStrings(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    printTheBackgroundInformation();
    callTheFunction(getTheFunctionCodeFromTheUser(), &errorCode);

    return errorCode;
}