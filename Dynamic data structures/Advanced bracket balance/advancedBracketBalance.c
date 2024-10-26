#include <stdio.h>
#include <stdbool.h>

#include "stack.h"

Stack* createSupportiveStack(const char *inputString) {
    int i = 0;
    Stack* stack = createStack();
    while (inputString[i] != '\0') {
        if (inputString[i] == ')') {
            push(stack, 1);
        }
        if (inputString[i] == '(') {
            push(stack, -1);
        }
        if (inputString[i] == ']') {
            push(stack, 2);
        }
        if (inputString[i] == '[') {
            push(stack, -2);
        }
        if (inputString[i] == '}') {
            push(stack, 3);
        }
        if (inputString[i] == '{') {
            push(stack, -3);
        }
        ++i;
    }
    return stack;
}

bool advanceBracketBalance(const char* inputString) {
    Stack* stack = createSupportiveStack(inputString);
    int balance = 0;
    if (stackSize(stack) % 2 == 1 || stackSize(stack) == 0) {
        return false;
    }
    while (isEmpty(stack) == false) {
        int previousValue = pop(stack);
        int currentValue = pop(stack);

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