#include "queue.h"
#include "stack.h"

#include <stdlib.h>

struct Queue {
    Stack* topStack;
    Stack* lowerStack;
};

Queue* createQueue(bool* errorCode) {
    Queue* queue = calloc(1, sizeof(Queue));
    if (queue == NULL) {
        *errorCode = true;
        return NULL;
    }
    queue->lowerStack = createStack(errorCode);
    if (*errorCode) {
        return NULL;
    }
    queue->topStack = createStack(errorCode);
    if (*errorCode) {
        return NULL;
    }
    return queue;
}

void deleteQueue(Queue* queue, bool* errorCode) {
    deleteStack(&queue->lowerStack, errorCode);
    deleteStack(&queue->lowerStack, errorCode);
}

Value dequeue(Queue* queue, bool* errorCode) {
    if (isEmpty(queue->lowerStack)) {
        while (!isEmpty(queue->topStack)) {
            push(queue->lowerStack, pop(queue->topStack, errorCode), errorCode);
        }
    }

    pop(queue->lowerStack, errorCode);
    if (*errorCode) {
        return 0;
    }
}

void enqueue(Queue* queue, Value value, bool* errorCode) {
    push(queue->topStack, value, errorCode);
}