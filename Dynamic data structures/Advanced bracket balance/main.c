#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "advancedBracketBalance.h"

int main(void) {
    Stack *stackOfParentheses = createStack();
    push(stackOfParentheses, 1);
    Stack *stackOfSquareBrackets = createStack();
    Stack *stackOfCurlyBraces = createStack();
    printf("%d", isEmpty(stackOfParentheses));
    return 0;
}