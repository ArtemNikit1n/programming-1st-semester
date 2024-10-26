#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include "stack.h"
#include "advancedBracketBalance.h"
#include "userInput.h"
#include "testsForAdvancedBracketBalance.h"
#include "testsForStack.h"

void runningTests(bool* errorCode) {
    if (!testAdvancedBracketBalance()) {
        printf("Тест testAdvancedBracketBalance не пройден\n");
        *errorCode = true;
    }
    if (!testCreateStack()) {
        printf("Тест testCreateStack не пройден\n");
        *errorCode = true;
    }
    if (!testDeleteStack()) {
        printf("Тест testDeleteStack не пройден\n");
        *errorCode = true;
    }
    if (!testIsEmpty()) {
        printf("Тест testIsEmpty не пройден\n");
        *errorCode = true;
    }
    if (!testPushAndStackSize()) {
        printf("Тест testPushAndStackSize не пройден\n");
        *errorCode = true;
    }
    if (!testPop()) {
        printf("Тест testPop не пройден\n");
        *errorCode = true;
    }
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    bool errorCode = false;

    runningTests(&errorCode);

    printf("Введите строку:\n");
    char* inputString = userInput();

    bool balance = advanceBracketBalance(inputString);

    if (!balance) {
        printf("Баланс скобок не соблюдён");
    } else {
        printf("Баланс скобок не нарушен");
    }
    free(inputString);

    return errorCode;
}