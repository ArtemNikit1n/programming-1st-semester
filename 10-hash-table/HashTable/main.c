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

    int hashTableSize = 70;
    //List* hashTable[1000] = { NULL };

    List** hashTable = calloc(hashTableSize, sizeof(List*));
    float* hashTableStatistics = buildHashTable(hashTable, "text.txt", &hashTableSize, &errorCode);
    printHashTable(hashTable, &hashTableSize, &errorCode);
    printf("\nHash table fill factor: %f\n"
        "Average length of list: %f\n"
        "max length of list: %d\n", hashTableStatistics[0], hashTableStatistics[1], (int)hashTableStatistics[2]);

    for (int i = 0; i < hashTableSize; ++i) {
        if (hashTable[i] != NULL) {
            deleteList(&hashTable[i]);
        }
    }
    free(hashTable);
}