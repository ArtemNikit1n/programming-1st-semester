#pragma once

// The structure indicating the beginning and end of the queue.
typedef struct Queue Queue;

// Adds a number to the top of the queue.
void enqueue(Queue* queue, int value);

// Removes a number from the end of the queue.
int dequeue(Queue* queue);

// Creates a queue.
Queue* createQueue();

// Checking whether the stack contains at least one element.
bool queueIsEmpty(Queue* queue);