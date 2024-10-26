#include <stdio.h>
#include <stdbool.h>

#include "stack.h"

Stack* createBinaryStack(char *inputString) {
    int i = 0;
    while (inputString[i] != '\0') {
        printf("%c ", inputString[i]);
        ++i;
    }
    //printf("%s", inputString);
    return NULL;
}

bool advanceBracketBalance(Stack* binaryStack) {
    //while (binaryStack->head != NULL) {
    //    if (binaryStack->head->value == 1) {
    //        break;
    //    }
    //}
    return 0;
}