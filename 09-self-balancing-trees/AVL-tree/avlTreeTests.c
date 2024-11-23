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
    //if (!testAddingAndDeleteKeys(errorCode)) {
    //    printf("AddingAndReadingValues's test failed\n");
    //    if (*errorCode) {
    //        printf("Error code: 1\n");
    //        return;
    //    }
    //    printf("Error code: 0\n");
    //    *errorCode = true;
    //    return;
    //}
}