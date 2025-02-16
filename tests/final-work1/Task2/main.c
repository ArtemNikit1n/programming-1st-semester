#include "testForStack.h"
#include "queue.h"

#include <stdio.h>
#include <stdbool.h>

void testTask2(bool* errorCode) {
    Queue* testQueue = createQueue(errorCode);
    enqueue(testQueue, 1, errorCode);
    enqueue(testQueue, 2, errorCode);
    enqueue(testQueue, 3, errorCode);
    if (*errorCode) {
        deleteQueue(testQueue, errorCode);
        return;
    }
    dequeue(testQueue, errorCode);
    dequeue(testQueue, errorCode);
    if (*errorCode) {
        deleteQueue(testQueue, errorCode);
        return;
    }
    deleteQueue(testQueue, errorCode);
}

int main(void) {
    bool errorCode = false;
    runStackTest(&errorCode);

    testTask2(&errorCode);
    if (errorCode) {
        printf("Tests failed");
    }
    else {
        printf("Tests passed");
    }

    return errorCode;
}