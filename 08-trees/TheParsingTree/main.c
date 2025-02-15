#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include "../Tree/tree.h"
#include "../Tree/testsFortree.h"
#include "../Stack/stack.h"
#include "../Stack/testsForStack.h"
#include "theParsingTree.h"
#include "testsForTheParsingTree.h"

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    bool errorCode = false;
    runTheTreeTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    runStackTest(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    runTheParsingTreeTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    const FILE* file = fopen("arithmeticExpression.txt", "r");
    if (file == NULL) {
        printf("���� �� ������\n");
        errorCode = true;
        return errorCode;
    }

    const Node* root = buildTree(file, &errorCode);
    fclose(file);

    printf("����������� ������ ��������� �� �����:\n");
    printAPostfixEntry(root, &errorCode);

    printf("\n��������� ����������: %d\n", calculateItFromTheTree(root, &errorCode));
    disposeNode(&root);
    return errorCode;
}