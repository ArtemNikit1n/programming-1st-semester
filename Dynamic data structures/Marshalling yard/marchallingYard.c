#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "../stack/stack.h"

Stack* infixToPostfix(char* inputString, bool *errorCode) {
    Stack* stack = createStack(errorCode);
    if (*errorCode) {
        return NULL;
    }
    char* endptr = inputString;
    const char numbers[] = "0123456789";
    const char binaryOperation[] = "*/+-";

    int i = 0;
    while (*endptr != '\0') {
        if (NULL != strchr(binaryOperation, *endptr)) {
            int value = strtol(endptr, &endptr, 10);
            push(stack, value, errorCode);
        }
        if (NULL != strchr(numbers, *endptr)) {
            int value = strtol(endptr, &endptr, 10);
        }
        while (*endptr == ' ') {
            ++endptr;
        }
    }
}