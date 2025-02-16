#include <stdio.h>
#include <stdbool.h>

#include "tree.h"

bool testDisposeAndCreate(bool* errorCode) {
    Node* testNode1 = createNode(0, errorCode);
    NodeValue testValue1 = getValue(testNode1, errorCode);
    bool test1 = testValue1 == 0;
    disposeNode(&testNode1);

    Node* testNode2 = createNode(32, errorCode);
    NodeValue testValue2 = getValue(testNode2, errorCode);
    bool test2 = testValue2 == 32;
    disposeNode(&testNode2);
    return !*errorCode && test1 && test2 && testNode2 == NULL && testNode1 == NULL;
}

bool testAddingAndReadingValues(bool* errorCode) {
    Node* testNode = createNode(0, errorCode);
    Node* test1LeftChild = createNode(-123, errorCode);
    Node* test2LeftChild = createNode(-321, errorCode);
    Node* testRightChild = createNode(321, errorCode);

    if (*errorCode) {
        disposeNode(&test2LeftChild);
        disposeNode(&testNode);
        return false;
    }

    addLeftChild(testNode, test1LeftChild, errorCode);
    addLeftChild(testNode, test2LeftChild, errorCode);

    Node* getLeftChildResult = getLeftChild(testNode, errorCode);
    NodeValue testValue1 = getValue(getLeftChildResult, errorCode);
    bool test1 = testValue1 == -321;

    addRightChild(testNode, testRightChild, errorCode);
    setValue(test1LeftChild, 123, errorCode);

    if (*errorCode) {
        disposeNode(&test2LeftChild);
        disposeNode(&testNode);
        return false;
    }

    NodeValue testValue2 = getValue(test1LeftChild, errorCode);
    NodeValue testValue3 = getValue(testRightChild, errorCode);
    bool test2 = testValue2 == 123;
    bool test3 = testValue3 == 321;

    disposeNode(&testNode);

    return test1 && test2 && test3;
}


void runTheTreeTests(bool* errorCode) {
    if (!testDisposeAndCreate(errorCode)) {
        printf("test disposeAndCreate failed\n");
        if (*errorCode) {
            printf("Error code: 1\n");
            return;
        }
        printf("Error code: 0\n");
        return;
    }
    if (!testAddingAndReadingValues(errorCode)) {
        printf("test addingAndReadingValues failed\n");
        if (*errorCode) {
            printf("Error code: 1\n");
            return;
        }
        printf("Error code: 0\n");
        *errorCode = true;
        return;
    }
}