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

    bool isHeightChanged = false;
    if (strcmp(key, node->value.key) > 0) {
        isHeightChanged = addNode(node->right, key, value, errorCode);
        if (isHeightChanged) {
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
        isHeightChanged = addNode(node->left, key, value, errorCode);
        if (isHeightChanged) {
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

Node* deleteNode(Node* node, const char* key, bool* isHeightChanged, bool* errorCode) {
    if (*errorCode) {
        return node;
    } 

    if (strcmp(node->value.key, key) == 0) {
        if (node->left == NULL && node->right == NULL) {
            *isHeightChanged = true;
            return NULL;
        }
        if (node->left != NULL && node->right == NULL) {
            *isHeightChanged = true;
            return node->left;
        }
        if (node->left == NULL && node->right != NULL) {
            *isHeightChanged = true;
            return node->right;
        }
        if (node->left != NULL && node->right != NULL) {
            Node* replacementNode = deleteNode(node, node->right->value.key, isHeightChanged, errorCode);
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

    Node* returnedNode = NULL;
    if (strcmp(node->value.key, key) < 0) {
        returnedNode = deleteNode(node->right, key, isHeightChanged, errorCode);

        if (returnedNode == NULL) {
            Node* saveDeletedNode = copyNode(node->right, errorCode);
            free(node->right);
            node->right = NULL;
            if (*isHeightChanged) {
                --node->balance;
                if (abs(node->balance) >= 1) {
                    *isHeightChanged = false;
                }
            }
            return saveDeletedNode;
        }
        else if (returnedNode == node->right->left || returnedNode == node->right->right) {
            Node* saveDeletedNode = copyNode(node->right, errorCode);
            free(node->right);
            node->right = returnedNode;
            if (*isHeightChanged) {
                --node->balance;
                if (abs(node->balance) >= 1) {
                    *isHeightChanged = false;
                }
            }
            return saveDeletedNode;
        }

        if (*isHeightChanged) {
            --node->balance;
            if (abs(node->balance) >= 1) {
                *isHeightChanged = false;
            }
        }
        return returnedNode;
    }
    if (strcmp(node->value.key, key) > 0) {
        returnedNode = deleteNode(node->left, key, isHeightChanged, errorCode);

        if (returnedNode == NULL) {
            Node* saveDeletedNode = copyNode(node->left, errorCode);
            free(node->left);
            node->left = NULL;
            if (*isHeightChanged) {
                ++node->balance;
                if (abs(node->balance) >= 1) {
                    *isHeightChanged = false;
                }
            }
            return saveDeletedNode;
        }
        else if (returnedNode == node->left->left || returnedNode == node->left->right) {
            Node* saveDeletedNode = copyNode(node->left, errorCode);
            free(node->left);
            node->left = returnedNode;
            if (*isHeightChanged) {
                ++node->balance;
                if (abs(node->balance) >= 1) {
                    *isHeightChanged = false;
                }
            }
            return saveDeletedNode;
        }

        if (*isHeightChanged) {
            ++node->balance;
            if (abs(node->balance) >= 1) {
                *isHeightChanged = false;
            }
        }
        return returnedNode;
    }
    if (returnedNode != NULL) {
        free(returnedNode);
    }
}