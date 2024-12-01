#include <stdio.h>
#include <stdlib.h>

#include "../list/testsForList.h"
#include "../list/list.h"
#include "hashTable.h"

int main(void) {
    bool errorCode = false;
    if (!runTheListTests(&errorCode)) {
        return errorCode;
    }

    List* hashTable[1000] = {NULL};
    buildHashTable(hashTable, "text.txt", &errorCode);
    printHashTable(hashTable, &errorCode);
}