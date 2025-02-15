#include <stdio.h>
#include <stdbool.h>

#include "stack.h"

bool testCreateStack(bool *errorCode) {
    Stack* testStack = createStack(errorCode);
    if (*errorCode) {
        printf("������� ��������� � �������\n");
        deleteStack(&testStack);
        return false;
    }
    bool testIsPassed = testStack != NULL;
    deleteStack(&testStack);
    return testIsPassed;
}

bool testDeleteStack(bool* errorCode) {
    Stack* testStack = createStack(errorCode);
    if (*errorCode) {
        printf("������� ��������� � �������\n");
        deleteStack(&testStack);
        return false;
    }
    push(testStack, 1, errorCode);
    push(testStack, 2, errorCode);
    push(testStack, 3, errorCode);
    if (*errorCode) {
        printf("������� ��������� � �������\n");
        deleteStack(&testStack);
        return false;
    }
    deleteStack(&testStack);
    return testStack == NULL;
}

bool testIsEmpty(bool* errorCode) {
    Stack* testStack = createStack(errorCode);
    if (*errorCode) {
        printf("������� ��������� � �������\n");
        deleteStack(&testStack);
        return false;
    }
    bool test1IsPassed = isEmpty(testStack);

    push(testStack, 1, errorCode);
    if (*errorCode) {
        printf("������� ��������� � �������\n");
        deleteStack(&testStack);
        return false;
    }
    bool test2IsPassed = !isEmpty(testStack);
    deleteStack(&testStack);
    return test1IsPassed && test2IsPassed;
}

bool testPush(bool* errorCode) {
    Stack* testStack = createStack(errorCode);
    if (*errorCode) {
        printf("������� ��������� � �������\n");
        deleteStack(&testStack);
        return false;
    }
    push(testStack, 1, errorCode);
    push(testStack, 2, errorCode);
    push(testStack, 3, errorCode);
    if (*errorCode) {
        printf("������� ��������� � �������\n");
        deleteStack(&testStack);
        return false;
    }
    bool testIsPassed = !isEmpty(testStack);
    deleteStack(&testStack);
    return testIsPassed;
}

bool testPop(bool* errorCode) {
    Stack* testStack = createStack(errorCode);
    if (*errorCode) {
        printf("������� ��������� � �������\n");
        deleteStack(&testStack);
        return false;
    }
    push(testStack, 1, errorCode);
    bool testIsPassed = pop(testStack, errorCode) == 1;
    if (*errorCode) {
        printf("������� ��������� � �������\n");
        deleteStack(&testStack);
        return false;
    }
    deleteStack(&testStack);
    return testIsPassed;
}

void runStackTest(bool* errorCode) {
    if (!testCreateStack(errorCode)) {
        printf("���� testCreateStack �� �������\n");
        *errorCode = true;
        return;
    }
    if (!testDeleteStack(errorCode)) {
        printf("���� testDeleteStack �� �������\n");
        *errorCode = true;
        return;
    }
    if (!testIsEmpty(errorCode)) {
        printf("���� testIsEmpty �� �������\n");
        *errorCode = true;
        return;
    }
    if (!testPush(errorCode)) {
        printf("���� testPushAndStackSize �� �������\n");
        *errorCode = true;
        return;
    }
    if (!testPop(errorCode)) {
        printf("���� testPop �� �������\n");
        *errorCode = true;
        return;
    }
}