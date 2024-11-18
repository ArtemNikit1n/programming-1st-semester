#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../Tree/tree.h"
#include "../Stack/stack.h"

Node* buildTree(FILE* file, bool* errorCode) {
    Node* root = NULL;
    Stack* stack = createStack(errorCode);
    if (*errorCode) {
        return NULL;
    }

    const char numbers[] = "0123456789";

    while (!feof(file)) {
        int theCurrentCharacter = getc(file);
        if (theCurrentCharacter == ' ' || theCurrentCharacter == '(' || theCurrentCharacter == ')') {
            continue;
        }

        bool isDigit = false;
        if (strchr(numbers, theCurrentCharacter) != NULL) {
            ungetc(theCurrentCharacter, file);
            fscanf(file, "%d", &theCurrentCharacter);
            isDigit = true;
        }

        Node* node = createNode(theCurrentCharacter, errorCode);
        if (root == NULL) {
            root = node;
            addLeftChild(node, NULL, errorCode);
            addRightChild(node, NULL, errorCode);
            push(stack, node, errorCode);
            continue;
        }

        Node* previousOperation = getStackValue(stack);
        if (getLeftChild(previousOperation, errorCode) == NULL) {
            addLeftChild(previousOperation, node, errorCode);
        } 
        else if (getRightChild(previousOperation, errorCode) == NULL) {
            addRightChild(previousOperation, node, errorCode);
            pop(stack, errorCode);
        }

        if (!isDigit) {
            push(stack, node, errorCode);
        }
    }
    return root;
}