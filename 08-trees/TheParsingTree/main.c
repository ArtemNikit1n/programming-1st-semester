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
    const FILE* file = fopen("arithmeticExpression.txt", "r");
    if (file == NULL) {
        printf("Файл не найден\n");
        errorCode = true;
        return errorCode;
    }

    const Node* tree = buildTree(file, &errorCode);

    fseek(file, 0, SEEK_END);
    long lengthFile = ftell(file);
    fclose(file);

    char* postfixEntry = calloc(lengthFile, sizeof(char));
    readingAPostfixEntry(tree, &errorCode);
    //printf("%s", postfixEntry);

    free(postfixEntry);

    return errorCode;
}