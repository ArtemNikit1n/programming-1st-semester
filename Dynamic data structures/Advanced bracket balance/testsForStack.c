#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

bool testCreateStack() {
    Stack* testStack = createStack();
    if (testStack != NULL) {
        return true;
    } else {
        return false;
    }
}

bool testDeleteStack() {
    Stack* testStack = createStack();
    push(testStack, 1);
    push(testStack, 2);
    push(testStack, 3);
    deleteStack(testStack);
    return isEmpty(testStack);
}

bool testIsEmpty() {
    Stack* testStack = createStack();
    if (isEmpty(testStack) == false) {
        return false;
    }
    push(testStack, 1);
    push(testStack, 2);
    push(testStack, 3);
    if (isEmpty(testStack) == true) {
        return false;
    }
    return true;
}

bool testPushAndStackSize() {
    Stack* testStack = createStack();
    push(testStack, 1);
    push(testStack, 2);
    push(testStack, 3);
    if (stackSize(testStack) == 3) {
        return true;
    } else {
        return false;
    }
}

bool testPop() {
    Stack* testStack = createStack();
    push(testStack, 1);
    push(testStack, 2);
    push(testStack, 3);
    pop(testStack);
    if (pop(testStack) != 2) {
        return false;
    }
    pop(testStack);
    return isEmpty(testStack);
}