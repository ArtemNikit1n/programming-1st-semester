#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "marchallingYard.h"
#include "../stack/stack.h"
#include "userInput.h"
#include "testsForUserInput.h"
#include "testsForQueue.h"
#include "../stack/testsForStack.h"

void runTests(bool* errorCode) {
    if (!testForEnqueueAndDequeue(errorCode)) {
        printf("Тест testForEnqueueAndDequeue() не пройден\n");
        *errorCode = true;
        return;
    }
    if (!testCheckingTheBalanceOfBrackets()) {
        printf("Тест testCheckingTheBalanceOfBrackets() не пройден\n");
        *errorCode = true;
        return;
    }
    if (!testCheckingUserInput()) {
        printf("Тест testCheckingUserInput не пройден\n");
        *errorCode = true;
        return;
    }
}

void bringOutTheStack(Stack* stack, bool *errorCode) {
    while (!isEmpty(stack)) {
        printf("%c", pop(stack, errorCode));
    }
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    bool errorCode = false;

    runTests(&errorCode);
    runStackTest(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    Stack* stack = createStack(&errorCode);
    push(stack, 154, &errorCode);
    bringOutTheStack(stack, &errorCode);

    printf("Введите выражение в постфиксной форме:\n"
        "Разрешённые символы: {0123456789+-*/( )}\n");

    char* infixForm = userInput();
    if (errorCode) {
        return errorCode;
    }
    Stack* postfixFormStack = infixToPostfix(infixForm, &errorCode);
    

    return errorCode;
}