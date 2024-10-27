#include <stdio.h>
#include <stdbool.h>

#include "queue.h"

bool testForEnqueueAndDequeue() {
    Queue* queue = createQueue();
    enqueue(queue, 1);
    enqueue(queue, 2);
    dequeue(queue);
    dequeue(queue);
    return queueIsEmpty(queue);
};