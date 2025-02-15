#define _CRT_SECURE_NO_WARNINGS

#include "workingWithAFile.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool saveToFile(struct NameAndPhoneNumber* records, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return true;
    }

    if (records->numberOfEntries == 0) {
        return false;
    }
    for (int i = 0; i < records->numberOfEntries; ++i) {
        fprintf(file, "%s - %s\n", records->names[i], records->phones[i]);
    }
    return false;
}

void addANewContact(struct NameAndPhoneNumber* records) {
    char name[MAX_RECORD_LENGTH] = "";
    char phone[MAX_RECORD_LENGTH] = "";
    bool theInputIsSuccessful = false;
    bool contactAdded = false;

    printf("������� ��� ������ ��������:\n");
    getchar();
    fscanf(stdin, "%s", name);
    if (strlen(name) >= MAX_RECORD_LENGTH - 1) {
        printf("������� ����� �������� � �����, ���������� ��� ���\n");
        addANewContact(records);
        return;
    }

    printf("������� ����� ��������:\n");
    getchar();
    fscanf(stdin, "%s", phone);
    if (strlen(phone) >= MAX_RECORD_LENGTH - 1) {
        printf("������� ����� �������� � ������ ��������, ���������� ��� ���\n");
        addANewContact(records);
        return;
    }

    printf("��������� ��������� �� ������� ���������� � ��������\n%s - %s\n", name, phone);
    printf("0 - � ���� ������ ���������\n1 - �� �����\n");
    while (!theInputIsSuccessful) {
        char input[5] = "";
        scanf("%s", &input);
        if (input[0] == '1' && input[1] == '\0') {
            theInputIsSuccessful = true;
            contactAdded = true;
        }
        else if (input[0] == '0' && input[1] == '\0') {
            theInputIsSuccessful = true;
            contactAdded = false;
        }
        else {
            theInputIsSuccessful = false;
            printf("�������� ����. ������� 1 ��� 0.\n");
        }
    }

    if (!contactAdded) {
        addANewContact(records);
    } else {
        strcpy(records->names[records->numberOfEntries], name);
        strcpy(records->phones[records->numberOfEntries], phone);
        records->numberOfEntries++;
        printf("������� ������!\n");
    }
}

bool readFromAFile(struct NameAndPhoneNumber* records, const char *filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return true;
    }

    char name[MAX_RECORD_LENGTH] = "";
    char phone[MAX_RECORD_LENGTH] = "";
    records->numberOfEntries = 0;

    while (fscanf(file, "%s - %s\n", name, phone) == 2) { 
        strcpy(records->names[records->numberOfEntries], name);
        strcpy(records->phones[records->numberOfEntries], phone);
        records->numberOfEntries++;
    }
    fclose(file);
    return false;
}

const char* getStringValueFromUser(void) {
    const int buffer = MAX_RECORD_LENGTH + 1;
    char* value = calloc(MAX_RECORD_LENGTH + 1, sizeof(char));
    if (value == NULL) {
        return NULL;
    }

    scanf("%51s", value);
    while (strlen(value) == buffer) {
        printf("������ ������ ������� �������. ���������� �����\n");
        while (getchar() != '\n');
        scanf("%51s", value);
    }
    return value;
}

const char* searchByName(struct NameAndPhoneNumber* records, const char *name) {
    for (int i = 0; i < records->numberOfEntries; ++i) {
        if (strcmp(name, &records->names[i]) == 0) {
            return records->phones[i];
        }
    }
    return NULL;
}

const char* searchByPhone(struct NameAndPhoneNumber* records, const char *phone) {
    for (int i = 0; i < records->numberOfEntries; ++i) {
        if (strcmp(phone, &records->phones[i]) == 0) {
            return records->names[i];
        }
    }
    return NULL;
}

void printAllAvailableRecords(struct NameAndPhoneNumber *records) {
    if (records->numberOfEntries == 0) {
        printf("\n�� ������� ������ ������ �����������\n");
        return;
    }
    printf("\n������� ������ (� ��� ����� �� ������������ � �����):\n\n");
    for (int i = 0; i < records->numberOfEntries; ++i) {
        printf("%d. %s - %s\n", i + 1, records->names[i], records->phones[i]);
    }
    printf("\n* ��� ���������� ���� ������ ������� 5\n");
}