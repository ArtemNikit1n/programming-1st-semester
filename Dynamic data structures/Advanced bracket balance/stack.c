#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "stack.h"

typedef struct StackElement {
    int value;
    struct StackElement* next;
} StackElement;

struct Stack {
    StackElement* head;
};

Stack* createStack() {
    return (Stack*)calloc(1, sizeof(Stack));
}

void deleteStack(Stack* stack) {
    while (stack->head != NULL) {
        void* next = stack->head->next;
        free(stack->head);
        stack->head = next;
    }
}

bool isEmpty(Stack* stack) {
    bool isEmpty = false;

    if (NULL == stack->head) {
        isEmpty = true;
    }
    return isEmpty;
}

void push(Stack* stack, int value) {
    StackElement* element = calloc(1, sizeof(StackElement));
    assert(element != NULL);
    element->value = value;
    element->next = stack->head;
    stack->head = element;
}

int pop(Stack* stack) {
    assert(stack->head != NULL);
    StackElement* tmp = stack->head;
    int value = stack->head->value;
    stack->head = stack->head->next;
    free(tmp);
    return value;
}

int stackSize(Stack* stack) {
    int size = 0;
    void* head = stack->head;
    while (stack->head != NULL) {
        stack->head = stack->head->next;
        ++size;
    }
    stack->head = head;
    return size;
}
