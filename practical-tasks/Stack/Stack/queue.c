#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

typedef struct QueueElement {
    int value;
    struct QueueElement* next;
} QueueElement;

struct Queue {
    QueueElement* front;
    QueueElement* back;
};

void Dequeue(Queue* queue) {
    QueueElement* tmp = queue->front;
    queue->front = queue->front->next;
    free(tmp);
}

/*Stack* createStack() {
    return (Stack*)calloc(1, sizeof(Stack));
}*/

void Enqueue(Queue* stack, int value) {
    QueueElement* element = malloc(sizeof(QueueElement));
    assert(element != NULL);
    element->value = value;
    element->next = stack->front;
    stack->front = element;
}
