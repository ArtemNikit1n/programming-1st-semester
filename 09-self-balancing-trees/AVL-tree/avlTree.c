#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "avlTree.h"

typedef struct Node {
    NodeValue value;
    Node* left;
    Node* right;
    short balance;
} Node;

Node* createTree(const char* key, const char* value, bool* errorCode) {
    Node* root = calloc(1, sizeof(Node));
    if (root == NULL) {
        *errorCode = true;
        return NULL;
    }
    root->value.key = key;
    root->value.value = value;
    return root;
}

void deleteTree(Node** root) {
    if (*root == NULL) {
        return;
    }
    deleteTree((&(*root)->left));
    deleteTree((&(*root)->right));
    free(*root);
    *root = NULL;
}

Node* getLeftChild(Node* node, bool* errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    return node->left;
}

Node* getRightChild(Node* node, bool* errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    return node->right;
}

NodeValue getValue(Node* node, bool* errorCode) {
    if (node == NULL) {
        NodeValue incorrectNodeValues = { .key = -1, .value = NULL };
        *errorCode = true;
        return incorrectNodeValues;
    }
    return node->value;
}

// ???
const char* searchByKey(Node* node, const char* key) {
    const char* foundValue = NULL;
    if (strcmp(node->value.key, key) == 0) {
        return node->value.value;
    }

    if ((node->left == NULL && strcmp(node->value.key, key) > 0) || (node->right == NULL && strcmp(node->value.key, key) < 0)) {
        return NULL;
    }

    if (strcmp(node->value.key, key) < 0) {
        foundValue = searchByKey(node->right, key);
    }
    if (strcmp(node->value.key, key) > 0) {
        foundValue = searchByKey(node->left, key);
    }
    return foundValue;
}
// ???

Node* balance(Node* node, bool* errorCode) {
    return node;
}

Node* addNode(Node* node, const char* key, const char* value, bool* errorCode) {
    if (node == NULL) {
        Node* newNode = createTree(key, value, errorCode);
        if (*errorCode) {
            return NULL;
        }
        return balance(newNode, errorCode);
    }
    if (strcmp(key, node->value.key) == 0) {
        node->value.value = value;
        return balance(node, errorCode);
    }
    if (strcmp(key, node->value.key) < 0) {
        node->left = addNode(node->left, key, value, errorCode);
        --node->balance;
    }
    if (strcmp(key, node->value.key) > 0) {
        node->right = addNode(node->right, key, value, errorCode);
        ++node->balance;
    }
    return balance(node, errorCode);
}

Node* copyNode(Node* node, bool* errorCode) {
    return NULL;
}

Node* deleteNode(Node* node, const char* key, bool* errorCode) {
    if (*errorCode) {
        return node;
    } 

    if (node->value.key == key) {
        if (node->left == NULL && node->right == NULL) {
            return NULL;
        }
        if (node->left != NULL && node->right == NULL) {
            return node->left;
        }
        if (node->left == NULL && node->right != NULL) {
            return node->right;
        }
        if (node->left != NULL && node->right != NULL) {
            int absoluteDifferenceParentAndLeftSon = abs(abs(node->left->value.key - abs(node->value.key)));
            int absoluteDifferenceParentAndRightSon = abs(abs(node->right->value.key) - abs(node->value.key));
            bool rightSonIsCloserToParent = absoluteDifferenceParentAndLeftSon > absoluteDifferenceParentAndRightSon;
            if (rightSonIsCloserToParent) {
                Node* replacementNode = deleteNode(node, node->right->value.key, errorCode);
                Node* saveNode = copyNode(node, errorCode);
                node->value.key = replacementNode->value.key;
                node->value = replacementNode->value;
                return saveNode;
            }
            else {
                Node* replacementNode = deleteNode(node, node->left->value.key, errorCode); 
                Node* saveNode = copyNode(node, errorCode);
                node->value.key = replacementNode->value.key;
                node->value.value = replacementNode->value.value;
                return saveNode;
            }
        }
    }

    if (node->left == NULL && node->right == NULL && node->value.key != key) {
        return node;
    }

    if (node->value.key < key) {
        Node* theReturnedNode = deleteNode(node->right, key, errorCode);

        if (theReturnedNode == NULL) {
            Node* saveDeletedNode = node->right;
            free(node->right);
            node->right = NULL;
            return saveDeletedNode;
        }
        else if (theReturnedNode == node->right->left || theReturnedNode == node->right->right) {
            Node* saveTheReturnedNode = copyNode(theReturnedNode, errorCode);
            Node* saveDeletedNode = copyNode(node->right, errorCode);
            node->right = saveTheReturnedNode;
            return saveDeletedNode;
        }
        return theReturnedNode;
    }
    if (node->value.key > key) {
        Node* theReturnedNode = deleteNode(node->left, key, errorCode);

        if (theReturnedNode == NULL) {
            Node* saveDeletedNode = copyNode(node->left , errorCode);
            node->left = NULL;
            return saveDeletedNode;
        }
        else if (theReturnedNode == node->left->left || theReturnedNode == node->left->right) {
            Node* saveTheReturnedNode = copyNode(theReturnedNode, errorCode);
            Node* saveDeletedNode = copyNode(node->left, errorCode);
            node->left = saveTheReturnedNode;
            return saveDeletedNode;
        }
        return theReturnedNode;
    }
}