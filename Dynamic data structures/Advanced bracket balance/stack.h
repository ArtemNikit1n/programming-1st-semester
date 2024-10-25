#pragma once

#include <stdbool.h>

typedef struct Stack Stack;

Stack* createStack();

bool isEmpty(Stack* stack);

void push(Stack* stack, int value);

void pop(Stack* stack);