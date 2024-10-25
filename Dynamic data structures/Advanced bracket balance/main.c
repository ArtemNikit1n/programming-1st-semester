#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "stack.h"
#include "advancedBracketBalance.h"

void runningTests(bool* errorCode) {
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

    Stack *stackOfParentheses = createStack();
    Stack *stackOfSquareBrackets = createStack();
    Stack *stackOfCurlyBraces = createStack();

    return errorCode;
}