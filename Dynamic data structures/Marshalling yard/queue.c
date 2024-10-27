#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>


#include "queue.h"

typedef struct QueueElement {
    int value;
    struct QueueElement* next;
} QueueElement;

typedef struct Queue {
    QueueElement* front;
    QueueElement* back;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->back = NULL;
    return queue;
}

void enqueue(Queue* queue, int value) {
    QueueElement* element = (QueueElement*)calloc(1, sizeof(QueueElement));
    element->value = value;

    if (queue->back == NULL) {
        queue->front = element;
        queue->back = element;
    } else {
        queue->back->next = element;
        queue->back = element;
    }
}

int dequeue(Queue* queue) {
    assert(queue->front != NULL);
    int value = queue->front->value;
    QueueElement* tmp = queue->front;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->back = NULL;
    }
    free(tmp);
    return value;
}

bool queueIsEmpty(Queue* queue) {
    if (queue->back == NULL) {
        return true;
    }
    return false;
}