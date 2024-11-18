#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "../Tree/tree.h"
#include "../Tree/testsFortree.h"
#include "../Stack/stack.h"
#include "../Stack/testsForStack.h"
#include "theParsingTree.h"

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;
    runTheTreeTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    //runStackTest(&errorCode);
    //if (errorCode) {
    //    return errorCode;
    //}
    FILE* file = fopen("arithmeticExpression.txt", "r");
    if (file == NULL) {
        printf("Файл не найден\n");
        errorCode = true;
        return errorCode;
    }

    Node* tree = buildTree(file, &errorCode);
    return errorCode;
}