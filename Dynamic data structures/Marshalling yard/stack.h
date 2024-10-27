#pragma once

#include <stdbool.h>

// A structure with a pointer to the beginning of the stack.
typedef struct Stack Stack;

// Allocating memory for a new stack.
Stack* createStack();

// Deletes the stack
void deleteStack(Stack* stack);

// Checking whether the stack contains at least one element.
bool isEmpty(Stack* stack);

// Adds an element to the end of the stack.
void push(Stack* stack, int value);

// Removes an element from the beginning of the stack. 
// Returns a deleted value.
int pop(Stack* stack);

// Returns the number of stack elements.
int stackSize(Stack* stack);