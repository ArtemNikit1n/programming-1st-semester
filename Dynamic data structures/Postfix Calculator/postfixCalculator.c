#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

int calculate(const char *inputString) {
    Stack* stack = createStack();
    char* endptr = inputString;
    const char numbers[] = "0123456789";
    int i = 0;
    while (*endptr != '\0') {

        if (NULL != strchr(numbers, *endptr)) {
            int value = strtol(endptr, &endptr, 10);
            push(stack, value);
        }
        while (*endptr == ' ') {
            ++endptr;
        }
        if (*endptr == '+') {
            int firstNumber = pop(stack);
            int secondNumber = pop(stack);
            push(stack, firstNumber + secondNumber);
            ++endptr;
        }
        if (*endptr == '-') {
            int firstNumber = pop(stack);
            int secondNumber = pop(stack);
            push(stack, secondNumber - firstNumber);
            ++endptr;
        }
        if (*endptr == '*') {
            int firstNumber = pop(stack);
            int secondNumber = pop(stack);
            push(stack, firstNumber * secondNumber);
            ++endptr;
        }
        if (*endptr == '/') {
            int firstNumber = pop(stack);
            int secondNumber = pop(stack);
            push(stack, secondNumber / firstNumber);
            ++endptr;
        }
    }
    assert(stackSize(stack) == 1);
    return pop(stack);
}