#pragma once

typedef struct Queue Queue;

Queue* createStack();

void Dequeue(Queue* queue, int value);

void Enqueue(Queue* queue);