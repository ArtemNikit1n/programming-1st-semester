#include <stdio.h>
#include <stdbool.h>

#include "../Stack/stack.h"

Stack* createSupportiveStack(const char *inputString, bool *errorCode) {
    int i = 0;
    Stack* stack = createStack();
    while (inputString[i] != '\0') {
        if (inputString[i] == ')') {
            push(stack, 1, errorCode);
        }
        if (inputString[i] == '(') {
            push(stack, -1, errorCode);
        }
        if (inputString[i] == ']') {
            push(stack, 2, errorCode);
        }
        if (inputString[i] == '[') {
            push(stack, -2, errorCode);
        }
        if (inputString[i] == '}') {
            push(stack, 3, errorCode);
        }
        if (inputString[i] == '{') {
            push(stack, -3, errorCode);
        }
        ++i;
    }
    return stack;
}

bool advanceBracketBalance(const char* inputString, bool *errorCode) {
    Stack* stack = createSupportiveStack(inputString, errorCode);
    int balance = 0;
    if (stackSize(stack) % 2 == 1 || stackSize(stack) == 0) {
        return false;
    }
    while (isEmpty(stack) == false) {
        int previousValue = pop(stack, errorCode);
        int currentValue = pop(stack, errorCode);

        if ((previousValue < currentValue) || (previousValue > 0 && currentValue < 0)) {
            balance += previousValue + currentValue;
            if (balance < 0) {
                return false;
            }
        }
        else {
            return false;
        }
    }
    return balance == 0;
}