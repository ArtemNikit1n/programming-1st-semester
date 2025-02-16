#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct StackElement {
    int value;
    struct StackElement* next;
} StackElement;

struct Stack {
    StackElement* head;
};

Stack* createStack(bool* errorCode) {
    Stack* stack = (Stack*)calloc(1, sizeof(Stack));
    if (NULL == stack) {
        *errorCode = true;
        return NULL;
    }
    return stack;
}

void deleteStack(Stack** pointerToStack, bool* errorCode) {
    if (*pointerToStack == NULL) {
        *errorCode = true;
        return;
    }

    while ((*pointerToStack)->head != NULL) {
        StackElement* next = (*pointerToStack)->head->next;
        free((*pointerToStack)->head);
        (*pointerToStack)->head = next;
    }
    free(*pointerToStack);
    *pointerToStack = NULL;
}

bool isEmpty(Stack* stack) {
    return NULL == stack->head;
}

void push(Stack* stack, int value, bool* errorCode) {
    StackElement* element = calloc(1, sizeof(StackElement));
    if (NULL == element) {
        *errorCode = true;
        return;
    }
    element->value = value;
    element->next = stack->head;
    stack->head = element;
}

int pop(Stack* stack, bool* errorCode) {
    if (stack->head == NULL) {
        *errorCode = true;
        return 0;
    }
    StackElement* tmp = stack->head;
    int value = stack->head->value;
    stack->head = stack->head->next;
    free(tmp);
    return value;
}