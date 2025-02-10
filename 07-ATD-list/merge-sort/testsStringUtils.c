#include "testsStringUtils.h"
#include "stringUtils.h"

#include <stdlib.h>

void testAllUtilitiesForStrings(bool* errorCode) {
    bool test1 = compareTwoString("123", "124") == 1;
    bool test2 = compareTwoString(NULL, "123") == -1;
    bool test3 = compareTwoString("123", NULL) == 1;
    bool test4 = compareTwoString(NULL, NULL) == 0;

    return test1 && test2 && test3 && test4;
}