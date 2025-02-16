#include "queue.h"

int main(void) {
    Queue* queue = createQueue();
    enqueue(queue, 5);
    printf("%d", dequeue(queue));
}