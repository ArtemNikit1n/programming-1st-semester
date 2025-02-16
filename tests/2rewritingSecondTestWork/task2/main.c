#include "testsForList.h"
#include "testTask1.h"

#include <stdbool.h>

int main(void) {
    bool errorCode = false;
    runTheListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    testTask1(&errorCode);
    return errorCode;
}