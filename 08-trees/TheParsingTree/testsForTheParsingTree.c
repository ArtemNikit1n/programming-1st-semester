#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "theParsingTree.h"
#include "../Tree/tree.h"

bool testBuildTreeAndCalculateItFromTheTree(bool* errorCode) {
    const FILE* test1File = fopen("test1.txt", "r");
    if (test1File == NULL) {
        *errorCode = true;
        return true;
    }
    const Node* test1Root = buildTree(test1File, errorCode);
    fclose(test1File);

    bool test1 = calculateItFromTheTree(test1Root, errorCode) == 25;

    const FILE* test2File = fopen("test2.txt", "r");
    if (test2File == NULL) {
        *errorCode = true;
        return true;
    }
    const Node* test2Root = buildTree(test2File, errorCode);
    fclose(test2File);

    bool test2 = calculateItFromTheTree(test2Root, errorCode) == -70;

    return test2;
}

void runTheParsingTreeTests(bool* errorCode) {
    if (!testBuildTreeAndCalculateItFromTheTree(errorCode)) {
        printf("���� testBuildTreeAndCalculateItFromTheTree �� �������\n");
        if (*errorCode) {
            printf("��� ������: 1\n");
            return;
        }
        printf("��� ������: 0\n");
        *errorCode = true;
        return;
    }
}