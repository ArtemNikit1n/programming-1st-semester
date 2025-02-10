#include <locale.h>
#include <stdio.h>
#include <stdbool.h>

#include "userInput.h"
#include "postfixCalculator.h"
#include "testsForPostfixCalculator.h"
#include "../Stack/testsForStack.h"

void runTests(bool* errorCode) {
    if (!testCalculate(errorCode)) {
        printf("Тест testCalculate не пройден\n");
        if (*errorCode) {
            printf("Код ошибки: 1");
        }
        *errorCode = true;
        return;
    }
    runStackTest(errorCode);
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    bool errorCode = false;

    runTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    printf("Введите выражение в постфиксной форме:\n"
        "Разрешённые символы: {0123456789+-*/ }\n");

    char* inputString = readUserInput(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    int calculatesResult = calculate(inputString, &errorCode);
    if (errorCode) {
        printf("Вычисления не были завершены\n");
        return errorCode;
    }
    printf("%d", calculatesResult);

    return errorCode;
}