#include <stdbool.h>

#include "avlTree.h"
#include "avlTreeTests.h"

int main(void) {
    bool errorCode = false;
    runAVLTreeTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    return errorCode;
}