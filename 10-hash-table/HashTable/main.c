#include <stdio.h>

#include "../list/testsForList.h"

int main(void) {
    bool errorCode = false;
    if (!runTheListTests(&errorCode)) {
        return errorCode;
    }
    return;
}