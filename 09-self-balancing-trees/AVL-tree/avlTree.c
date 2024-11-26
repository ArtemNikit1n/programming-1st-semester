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

Node* rotateLeft(Node* a) {
    Node* b = a->right;
    Node* c = b->left;
    b->left = a;
    a->right = c;
    return a;
    return b;
}

Node* rotateRight(Node* node) {
    return node;
}

Node* bigRotateLeft(Node* node) {
    return node;
}

Node* bigRotateRight(Node* node) {
    return node;
}

Node* balance(Node* node, bool* errorCode) {
    if (node->balance == 2) {
        if (node->right->balance >= 0) {
            return rotateLeft(node);
        }
        return bigRotateLeft(node);
    }
    if (node->balance == -2) {
        if (node->left->balance <= 0) {
            return rotateRight(node);
        }
        return bigRotateRight(node);
    }
    return node;
}

bool addNode(Node* node, const char* key, const char* value, bool* errorCode) {
    static bool changeBalance = false;

    if (strcmp(key, node->value.key) == 0) {
        node->value.value = value;
        return false;
    }

    if (node->left == NULL && strcmp(key, node->value.key) < 0) {
        Node* newNode = createTree(key, value, errorCode);
        if (*errorCode) {
            return false;
        }
        node->left = newNode;

        --node->balance;
        if (node->balance == 0) {
            return false;
        }
        else {
            return true;
        }
    }
    else if (node->right == NULL && strcmp(key, node->value.key) > 0) {
        Node* newNode = createTree(key, value, errorCode);
        if (*errorCode) {
            return false;
        }
        node->right = newNode;

        ++node->balance;
        if (node->balance == 0) {
            return false;
        }
        else {
            return true;
        }
    }

    bool needChangeBalance = false;
    if (strcmp(key, node->value.key) > 0) {
        needChangeBalance = addNode(node->right, key, value, errorCode);
        if (needChangeBalance) {
            ++node->balance;
            if (node->balance == 0) {
                return false;
            }
            else {
                return true;
            }
        }
        return false;
    }
    if (strcmp(key, node->value.key) < 0) {
        needChangeBalance = addNode(node->left, key, value, errorCode);
        if (needChangeBalance) {
            --node->balance;
            if (node->balance == 0) {
                return false;
            }
            else {
                return true;
            }
        }
        return false;
    }
}

Node* copyNode(const Node* source, bool* errorCode) {
    if (source == NULL) {
        *errorCode = true;
        return NULL;
    }

    Node* destination = createTree(source->value.key, source->value.value, errorCode);
    if (*errorCode) {
        return NULL;
    }

    return destination;
}

Node* deleteNode(Node* node, const char* key, bool* errorCode) {
    if (*errorCode) {
        return node;
    } 

    if (strcmp(node->value.key, key) == 0) {
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
            Node* replacementNode = deleteNode(node, node->right->value.key, errorCode);
            Node* saveNode = copyNode(node, errorCode);
            node->value.key = replacementNode->value.key;
            node->value = replacementNode->value;
            free(replacementNode);
            return saveNode;
        }
    }

    if (node->left == NULL && node->right == NULL && strcmp(node->value.key, key) != 0) {
        return node;
    }

    Node* theReturnedNode = NULL;
    if (strcmp(node->value.key, key) < 0) {
        theReturnedNode = deleteNode(node->right, key, errorCode);

        if (theReturnedNode == NULL) {
            Node* saveDeletedNode = copyNode(node->right, errorCode);
            free(node->right);
            node->right = NULL;
            return saveDeletedNode;
        }
        else if (theReturnedNode == node->right->left || theReturnedNode == node->right->right) {
            Node* saveDeletedNode = copyNode(node->right, errorCode);
            free(node->right);
            node->right = theReturnedNode;
            return saveDeletedNode;
        }
        return theReturnedNode;
    }
    if (strcmp(node->value.key, key) > 0) {
        theReturnedNode = deleteNode(node->left, key, errorCode);

        if (theReturnedNode == NULL) {
            Node* saveDeletedNode = copyNode(node->left, errorCode);
            free(node->left);
            node->left = NULL;
            return saveDeletedNode;
        }
        else if (theReturnedNode == node->left->left || theReturnedNode == node->left->right) {
            Node* saveDeletedNode = copyNode(node->left, errorCode);
            free(node->left);
            node->left = theReturnedNode;
            return saveDeletedNode;
        }
        return theReturnedNode;
    }
    if (theReturnedNode != NULL) {
        free(theReturnedNode);
    }
}