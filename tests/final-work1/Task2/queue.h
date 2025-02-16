#pragma once

#include <stdbool.h>

// The type of values stored in the queue.
typedef int Value;

// The abstract data type is a queue.
typedef struct Queue Queue;

// Creates a queue.
Queue* createQueue(bool* errorCode);

// Creates a queue.
void deleteQueue(Queue* queue, bool* errorCode);

// Removes from the beginning.
Value dequeue(Queue* queue, bool* errorCode);

// Adds it to the end of the queue.
void enqueue(Queue* queue, Value value, bool* errorCode);