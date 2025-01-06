#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "marchallingYard.h"

void testTheMarshallingYard(bool *errorCode) {
    const char* postfixForm1 = infixToPostfix("2 + 2 * 2", errorCode);
    if (*errorCode) {
        free(postfixForm1);
        return;
    }
    bool test1 = strcmp(postfixForm1, "2 2 2 * +") == 0;
    free(postfixForm1);

    const char* postfixForm2 = infixToPostfix("(1 + 1) * 2", errorCode);
    if (*errorCode) {
        free(postfixForm2);
        return;
    }
    bool test2 = strcmp(postfixForm2, "1 1 + 2 *") == 0;
    free(postfixForm2);

    const char* postfixForm3 = infixToPostfix("(1 + 12312432) * 123 + (0 - 123)", errorCode);
    if (*errorCode) {
        free(postfixForm3);
        return;
    }
    bool test3 = strcmp(postfixForm3, "1 12312432 + 123 * 0 123 - + ") == 0;
    free(postfixForm3);

    const char* postfixForm4 = infixToPostfix("(((())))", errorCode);
    if (*errorCode) {
        free(postfixForm4);
        return;
    }
    bool test4 = postfixForm4 == NULL;
    free(postfixForm4);

    if (!(test1 && test2 && test3 && test4)) {
        *errorCode = true;
        return;
    }
}