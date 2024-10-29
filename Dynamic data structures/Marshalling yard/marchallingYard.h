#pragma once

#include "../Stack/stack.h"

// Accepts a string in infix form, returns a stack containing the postfix form.
Stack* infixToPostfix(char* inputString, bool* errorCode);