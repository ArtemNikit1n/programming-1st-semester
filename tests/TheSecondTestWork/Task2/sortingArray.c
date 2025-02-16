#include <stdbool.h>
#include <stdio.h>

#include "tree.h"

void addToSearchTree(Node* node, const int value, bool* errorCode) {
    if (getLeftChild(node, errorCode) == NULL && getValue(node, errorCode) >= value) {
        if (*errorCode) {
            return;
        }
        Node* newNode = createNode(value, errorCode);
        if (*errorCode) {
            return;
        }
        addLeftChild(node, newNode, errorCode);
        return;
    }
    else if (getRightChild(node, errorCode) == NULL && getValue(node, errorCode) < value) {
        if (*errorCode) {
            return;
        }
        Node* newNode = createNode(value, errorCode);
        if (*errorCode) {
            return;
        }
        addRightChild(node, newNode, errorCode);
        return;
    }

    if (getValue(node, errorCode) < value) {
        addToSearchTree(getRightChild(node, errorCode), value, errorCode);
    }
    if (getValue(node, errorCode) >= value) {
        addToSearchTree(getLeftChild(node, errorCode), value, errorCode);
    }
}

void sortBySymmetricTraversal(Node* root, int array[], int *indexToInsert, bool *errorCode) {
    if (root == NULL) {
        return;
    }
    sortBySymmetricTraversal(getLeftChild(root, errorCode), array, indexToInsert, errorCode);
    array[*indexToInsert] = getValue(root, errorCode);
    ++(*indexToInsert);
    sortBySymmetricTraversal(getRightChild(root, errorCode), array, indexToInsert, errorCode);
}

void sortByBuildingTree(int array[], int arraySize, bool *errorCode) {
    if (arraySize < 1 || array == NULL) {
        return;
    }

    Node* searchTree = createNode(array[0], errorCode);
    for (int i = 1; i < arraySize; ++i) {
        addToSearchTree(searchTree, array[i], errorCode);
    }
    if (*errorCode) {
        disposeNode(&searchTree);
        return;
    }

    int indexToInsert = 0;
    sortBySymmetricTraversal(searchTree, array, &indexToInsert, errorCode);

    disposeNode(&searchTree);
}