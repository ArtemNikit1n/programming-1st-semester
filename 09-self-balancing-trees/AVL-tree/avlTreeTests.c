#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "avlTree.h"
#include "avlTreeTests.h"

bool testDeleteTreeAndCreateTree(bool* errorCode) {
    Node* testNode1 = createTree("32", "abc", errorCode);
    deleteTree(&testNode1);
    testNode1 = createTree("456", "def", errorCode);
    bool test1 = strcmp(searchByKey(testNode1, "456"), "def") == 0;
    bool test2 = !(searchByKey(testNode1, "321"), "def") == NULL;
    deleteTree(&testNode1);
    deleteTree(&testNode1);

    return !*errorCode && test1 && test2 && testNode1 == NULL;
}

bool testAddingAndDeleteNode(bool* errorCode) {
    Node* root = createTree("o", "15", errorCode);
    addNode(root, "f", "6", errorCode);
    addNode(root, "t", "20", errorCode);
    addNode(root, "s", "19", errorCode);
    addNode(root, "u", "21", errorCode);
    addNode(root, "h", "8", errorCode);

    if (*errorCode) {
        deleteTree(&root);
        return false;
    }

    bool test1 = searchByKey(root, "m") == NULL;
    bool test2 = strcmp(searchByKey(root, "h"), "8") == 0;
    bool test3 = strcmp(searchByKey(root, "t"), "20") == 0;
    bool test4 = strcmp(searchByKey(root, "o"), "15") == 0;

    if (*errorCode) {
        deleteTree(&root);
        return false;
    }

    deleteNode(root, "u", errorCode);
    deleteNode(root, "t", errorCode);
    bool test5 = searchByKey(root, "u") == NULL;
    bool test6 = searchByKey(root, "t") == NULL;

    if (*errorCode) {
        deleteTree(&root);
        return false;
    }

    addNode(root, "c", "3", errorCode);
    addNode(root, "e", "5", errorCode);
    addNode(root, "k", "11", errorCode);
    addNode(root, "j", "10", errorCode);

    deleteNode(root, "f", errorCode);
    bool test7 = searchByKey(root, "f") == NULL;

    deleteTree(&root);

}

void runAVLTreeTests(bool* errorCode) {
    if (!testDeleteTreeAndCreateTree(errorCode)) {
        printf("DisposeAndCreate's test failed\n");
        if (*errorCode) {
            printf("Error code: 1\n");
            return;
        }
        printf("Error code: 0\n");
        *errorCode = true;
        return;
    }
    if (!testAddingAndDeleteNode(errorCode)) {
        printf("AddingAndReadingValues's test failed\n");
        if (*errorCode) {
            printf("Error code: 1\n");
            return;
        }
        printf("Error code: 0\n");
        *errorCode = true;
        return;
    }
}