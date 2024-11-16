#include <stdio.h>
#include <stdbool.h>

#include "../Tree/tree.h"

NodeValue createNodeValue(int key, char* value) {
    NodeValue nodeValue = { .key = key, .value = value };
    return nodeValue;
}

void addToTheDictionary(Node* node, const int key, const char* value, bool* errorCode) {
    if (getValue(node, errorCode).key == key) {
        setValue(node, createNodeValue(key, value), errorCode);
        return;
    }

    if (getLeftChild(node, errorCode) == NULL && getValue(node, errorCode).key > key) {
        if (*errorCode) {
            return;
        }
        Node* newNode = createNode(createNodeValue(key, value), errorCode);
        if (*errorCode) {
            return;
        }
        addLeftChild(node, newNode, errorCode);
        return;
    }
    else if (getRightChild(node, errorCode) == NULL && getValue(node, errorCode).key < key) {
        if (*errorCode) {
            return;
        }
        Node* newNode = createNode(createNodeValue(key, value), errorCode);
        if (*errorCode) {
            return;
        }
        addRightChild(node, newNode, errorCode);
        return;
    }

    if (getValue(node, errorCode).key < key) {
        addToTheDictionary(getRightChild(node, errorCode), key, value, errorCode);
    }
    if (getValue(node, errorCode).key > key) {
        addToTheDictionary(getLeftChild(node, errorCode), key, value, errorCode);
    }
}

char* findItByTheKey(Node* node, const int key, bool* errorCode) {
    if (*errorCode) {
        return;
    }

    if (getValue(node, errorCode).key == key) {
        return getValue(node, errorCode).value;
    }

    if (getLeftChild(node, errorCode) == NULL && getRightChild(node, errorCode) == NULL && getValue(node, errorCode).key != key) {
        return NULL;
    }

    if (getValue(node, errorCode).key < key) {
        findItByTheKey(getRightChild(node, errorCode), key, errorCode);
    }
    if (getValue(node, errorCode).key > key) {
        findItByTheKey(getLeftChild(node, errorCode), key, errorCode);
    }
}