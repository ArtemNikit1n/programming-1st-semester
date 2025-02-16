#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

void swap(char* first, char* second) {
    if (*first == *second) {
        return;
    }
    *first ^= *second;
    *second ^= *first;
    *first ^= *second;
}

void printCharArray(char charArray[]) {
    int i = 0;
    while (charArray[i] != '\0') {
        printf("%c", charArray[i]);
        ++i;
    }
}

void arrayReversal(char array[], const int lengthArray) {
    int middleOfTheArray = (int)(lengthArray / 2);

    for (int i = 0; i < middleOfTheArray; ++i) {
        swap(&array[i], &array[lengthArray - 1 - i]);
    }
}

void copyingALineWithoutSpaces(char incomingString[], char cloneString[]) {
    int i = 0;
    int j = 0;
    while (incomingString[i] != '\0') {
        if (incomingString[i] != ' ') {
            cloneString[j] = incomingString[i];
            ++j;
            ++i;
        }
        else {
            ++i;
        }
    }
    cloneString[j] = '\0';
}

bool task1(char incomingString[]) {
    bool result = false;

    setlocale(LC_ALL, "Rus");
    char string[1000];
    char reversalString[1000];

    copyingALineWithoutSpaces(incomingString, string);
    copyingALineWithoutSpaces(string, reversalString);
    int stringLength = strlen(string);
    arrayReversal(reversalString, stringLength);

    if (strcmp(string, reversalString) == 0) {
        result = true;
    }
    return result;
}

bool testTask1() {
    setlocale(LC_ALL, "Rus");
    char testString1[35] = "я иду с мечем судия";
    char testString2[35] = "abcd fg";
    return task1(testString1) == 1 && task1(testString2) == 0;
}

int main(void) {
    bool errorCode = false;
    if (!testTask1()) {
        errorCode = true;
        printf("Test failed");
    } else {
        printf("Tests passed");
    }
    return errorCode;
}