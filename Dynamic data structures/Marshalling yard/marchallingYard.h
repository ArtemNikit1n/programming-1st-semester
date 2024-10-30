#pragma once

#include "../Stack/stack.h"

// Accepts a string in infix form, returns a postfix form.
char* infixToPostfix(char* inputString, bool* errorCode);