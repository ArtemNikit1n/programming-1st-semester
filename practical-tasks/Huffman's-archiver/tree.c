#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

typedef struct Node {
    NodeValue value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

Node* createNode(NodeValue value, bool* errorCode) {
    Node* node = calloc(1, sizeof(Node));
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    node->value = value;
    return node;
}

void addLeftChild(Node* node, Node* child, bool* errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return;
    }
    node->leftChild = child;
}

void addRightChild(Node* node, Node* child, bool* errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return;
    }
    node->rightChild = child;
}

Node* getLeftChild(Node* node, bool* errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    return node->leftChild;
}

Node* getRightChild(Node* node, bool* errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    return node->rightChild;
}

NodeValue getValue(Node* node, bool* errorCode) {
    if (node == NULL) {
        NodeValue incorrectNodeValues = { .frequency = -1, .value = 0 };
        *errorCode = true;
        return incorrectNodeValues;
    }
    return node->value;
}

void setValue(Node* node, NodeValue value, bool* errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return;
    }
    node->value = value;
}

void disposeNode(Node* node) {
    if (node == NULL) {
        return;
    }

    disposeNode(node->leftChild);
    disposeNode(node->rightChild);
    free(node);
}

