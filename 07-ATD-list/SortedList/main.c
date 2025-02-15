#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "sortedList.h"
#include "../listForSortedList/list.h"
#include "../listForSortedList/testsForlist.h"
#include "testsForSortedList.h"

void printTheBackgroundInformation(void) {
    printf(
        "0 � �����\n"
        "1 � �������� �������� � ������������� ������\n"
        "2 � ������� �������� �� ������\n"
        "3 � ����������� ������\n");
}

int getIntValueFromUser(void) {
    int value = -1;
    int scanfReturns = scanf("%d", &value);
    while (scanfReturns != 1) {
        printf("����� ������� �����������, ���������� ��� ���\n");
        while (getchar() != '\n');
        scanfReturns = scanf("%d", &value);
    }
    return value;
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
            printf("������� �����, ������� �� ������ �������� � ������\n");
            addItToSortedList(list, getIntValueFromUser(), errorCode);

            if (*errorCode) {
                printf("��� ���������� ����� ��������� ������\n");
                *errorCode = false;
            } else {
                ++listLength;
                printf("����� ���� ������� ���������!\n");
            }
        }

        if (functionCode == 2) {
            if (listLength == 0) {
                printf("������ ����\n");
                functionCode = getIntValueFromUser();
                while (functionCode > 3 || functionCode < 0) {
                    printf("����� ����� ���� ������ �� 1 �� 3\n");
                    functionCode = getIntValueFromUser();
                }
                continue;
            }

            printf("������� ��������, ������� �� ������ ������� �� ������\n");

            int valueToDelete = getIntValueFromUser();
            deleteFromSortedList(list, valueToDelete, errorCode);

            if (*errorCode) {
                printf("��� �������� �������� ��������� ������\n");
                *errorCode = false;
            } else {
                printf("�������� ������� �������\n");
                --listLength;
            }
        }

        if (functionCode == 3) {
            if (listLength == 0) {
                printf("������ ����\n");
            } else {
                printList(list, errorCode);
            }
        }

        functionCode = getIntValueFromUser();
        while (functionCode > 3 || functionCode < 0) {
            printf("����� ����� ���� ������ �� 1 �� 3\n");
            functionCode = getIntValueFromUser();
        }
    }
    deleteList(&list);
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

    printTheBackgroundInformation();
    int functionCode = getIntValueFromUser();
    while (functionCode > 3 || functionCode < 0) {
        printf("����� ����� ���� ������ �� 1 �� 3\n");
        functionCode = getIntValueFromUser();
    }
    callTheFunction(functionCode, &errorCode);

    return errorCode;
}