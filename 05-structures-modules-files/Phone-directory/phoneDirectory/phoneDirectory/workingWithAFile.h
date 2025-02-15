#pragma once

#include <stdbool.h>

#define MAX_RECORD_LENGTH 50
#define MAX_ENTRIES 100

// ��������� ��� �������� ������ � ������� � ������.
struct NameAndPhoneNumber {
    char names[MAX_ENTRIES][MAX_RECORD_LENGTH];
    char phones[MAX_ENTRIES][MAX_RECORD_LENGTH];
    int numberOfEntries;
};

// ��������� ��� � ������� � ��������� NameAndPhoneNumber.
void addANewContact(struct NameAndPhoneNumber* records);

// ������ ������, ������� ��� ���������� � �����, � ��������� �� � ��������� NameAndPhoneNumber. ���������� false ��� ������� �������� �����.
bool readFromAFile(struct NameAndPhoneNumber* records, const char *filename);

// ������� ���������� ��������� NameAndPhoneNumber � �������� � �������.
void printAllAvailableRecords(struct NameAndPhoneNumber* records);

// ����� �������� � ���������. ���������� true, ���� ������� ������.
const char* searchByName(struct NameAndPhoneNumber* records, const char *name);

// ������� ��� ��������� �������� ��� ������ �� ������������.
const char* getStringValueFromUser(void);

// ����� ����� � ���������. ���������� true, ���� ��� �������.
const char* searchByPhone(struct NameAndPhoneNumber* records, const char *phone);

// ������� ��� ���������� ������ �� ��������� � ����. ���������� false ��� ������� �������� �����.
bool saveToFile(struct NameAndPhoneNumber* records, const char *filename);