#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool checkBalanceOfBrackets(const char* string) {
    int balance = 0;
    int i = 0;
    while (string[i] != '\0') {
        if (balance < 0) {
            return false;
        }
        else if (string[i] == '(') {
            balance += 1;
        }
        else if (string[i] == ')') {
            balance -= 1;
        }
        ++i;
    }
    return balance == 0;
}

bool checkingUserInput(const char* string) {
    if (NULL == string) {
        return false;
    }

    const char correctCharacters[] = "0123456789+-*/( )";
    int i = 0;

    while (string[i] != '\0') {
        if (NULL == strchr(correctCharacters, string[i])) {
            return false;
        }
        ++i;
    }

    return true;
}

char* userInput(bool* errorCode) {
    const int buffer = 101;
    char* inputString = calloc(101, sizeof(char));

    scanf("%101s", inputString);
    while (strlen(inputString) == buffer || !checkBalanceOfBrackets(inputString) || !checkingUserInput(inputString)) {
        printf("Ошибка ввода, попробуйте ещё раз:\n");
        while (getchar() != '\n');
        scanf("%101s", inputString);
    }
    return inputString;
}