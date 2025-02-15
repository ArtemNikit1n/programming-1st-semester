#define _CRT_SECURE_NO_WARNINGS

#include "workingWithAFile.h"
#include "testsWorkingWithAFile.h"

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

void printReferenceInformation(void) {
    printf("\n------------------"
        "\n������� ����:"
        "\n0 - �����"
        "\n1 - �������� ������ (��� � �������)"
        "\n2 - ����������� ��� ��������� ������"
        "\n3 - ����� ������� �� �����"
        "\n4 - ����� ��� �� ��������"
        "\n5 - ��������� ������� ������ � ����\n");
}

int readUserInput(void) {
    printReferenceInformation();
    printf("\n������� �������: ");

    int functionCode = -1;
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 5 || functionCode < 0 || scanfReturns != 1) {
        printf("\n������������ ����� �������, ���������� ��� ���\n");
        printReferenceInformation();
        while (getchar() != '\n');
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

void launchPhoneDirectory(struct NameAndPhoneNumber* records, int commandNumber) {
    while (commandNumber != 0) {
        if (commandNumber == 1) {
            printf("\n���������� ������\n\n");
            addANewContact(records);
        }
        else if (commandNumber == 2) {
            printAllAvailableRecords(records);
        }
        else if (commandNumber == 3) {
            printf("\n������� ��� �������� ��������:\n\n");
            const char* name = getStringValueFromUser();
            if (name == NULL) {
                printf("\n������ ��������� ������, ���������� ��� ���");
                commandNumber = readUserInput();
                continue;
            }

            const char* foundPhone = searchByName(records, name);
            free(name);
            if (foundPhone == NULL) {
                printf("\n������� �� ������");
            }
            printf("\n%s", foundPhone);
        }
        else if (commandNumber == 4) {
            printf("\n������� ������� �������� ��������:\n\n");
            const char* phone = getStringValueFromUser();
            if (phone == NULL) {
                printf("\n������ ��������� ������, ���������� ��� ���");
                commandNumber = readUserInput();
                continue;
            }

            const char* foundName = searchByPhone(records, phone);
            free(phone);
            if (foundName == NULL) {
                commandNumber = readUserInput();
                printf("\n��� �� �������");
                continue;
            }
            printf("\n%s", foundName);
        }
        else if (commandNumber == 5) {
            if (saveToFile(records, "phoneDatabase.txt")) {
                printf("\n������ �������� �����, ���������� ��� ���");
            }
            printf("\n�������� ������� ��������� � ����\n");
        }
        commandNumber = readUserInput();
    }
    printf("����� �� �����������...\n");

}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    if (!testSearchByName()) {
        printf("���� testSearchByName �� �������");
        return true;
    }

    if (!testSearchByPhone()) {
        printf("���� testSearchByPhone �� �������");
        return true;
    }

    int commandNumber = readUserInput();
    struct NameAndPhoneNumber records = {
        .numberOfEntries = 0,
        .names = { { '\0' } },
        .phones = { { '\0' } }
    };

    if (readFromAFile(&records, "phoneDatabase.txt")) {
        printf("\n������ �������� �����");
        return true;
    }
    launchPhoneDirectory(&records, commandNumber);

    return false;
}