#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "../stack/stack.h"
#include "queue.h"

char* queueToString(Queue* queue, const int inputStringLength, bool* errorCode) {
    if (queue == NULL || queueIsEmpty(queue)) {
        *errorCode = true;
        return NULL;
    }

    size_t maxLen = inputStringLength * 2;
    char* postfixForm = (char*)malloc(maxLen * sizeof(char));
    if (postfixForm == NULL) {
        *errorCode = true;
        return NULL;
    }

    int i = 0;
    while (!queueIsEmpty(queue)) {
        postfixForm[i++] = dequeue(queue, errorCode);
    }
    postfixForm[i] = '\0';

    return postfixForm;
}

char* infixToPostfix(const char* inputString, bool *errorCode) {
    Stack* stack = createStack(errorCode);
    Queue* queue = createQueue(errorCode);
    if (*errorCode) {
        deleteQueue(&queue);
        deleteStack(&stack);
        return NULL;
    }

    const char numbers[] = "0123456789";
    const char binaryOperation[] = "*/+-";
    char *inputStringWithoutSpaces = malloc(strlen(inputString) * sizeof(char));
    if (inputStringWithoutSpaces == NULL) {
        deleteQueue(&queue);
        deleteStack(&stack);
        return NULL;
    }
    int j = 0;
    for (int i = 0; i < strlen(inputString); i++) {
        if (inputString[i] != ' ') {
            inputStringWithoutSpaces[j++] = inputString[i];
        }
    }
    inputStringWithoutSpaces[j] = '\0';

    int i = 0;
    bool previousTokenIsADigit = false;
    while (inputStringWithoutSpaces[i] != '\0') {
        if (strchr(numbers, inputStringWithoutSpaces[i]) != NULL) {
            enqueue(queue, inputStringWithoutSpaces[i], errorCode);
            enqueue(queue, ' ', errorCode);
            if (*errorCode) {
                deleteQueue(&queue);
                deleteStack(&stack);
                return NULL;
            }
            previousTokenIsADigit = true;
            ++i;
            continue;
        }

        if (strchr(binaryOperation, inputStringWithoutSpaces[i]) != NULL) {
            char opreator = pop(stack, errorCode);
            if (*errorCode) {
                *errorCode = false;
                push(stack, inputStringWithoutSpaces[i], errorCode);
                previousTokenIsADigit = false;
                ++i;
                continue;
            } else {
                while (opreator == '*' || opreator == '/') {
                    enqueue(queue, opreator, errorCode);
                    enqueue(queue, ' ', errorCode);
                    opreator = pop(stack, errorCode);
                    if (*errorCode) {
                        *errorCode = false;
                        break;
                    }
                }
                push(stack, opreator, errorCode);
                push(stack, inputStringWithoutSpaces[i], errorCode);
                previousTokenIsADigit = false;
                ++i;
                continue;
            }
        }

        if (inputStringWithoutSpaces[i] == '(') {
            push(stack, inputStringWithoutSpaces[i], errorCode);
            if (*errorCode) {
                deleteQueue(&queue);
                deleteStack(&stack);
                return NULL;
            }
            previousTokenIsADigit = false;
            ++i;
            continue;
        }

        if (inputStringWithoutSpaces[i] == ')') {
            char stackHead = pop(stack, errorCode);
            while (stackHead != '(') {
                enqueue(queue, stackHead, errorCode);
                enqueue(queue, ' ', errorCode);
                stackHead = pop(stack, errorCode);
            }
            previousTokenIsADigit = false;
            ++i;
            continue;
        }
        ++i;
    }
    while (!isEmpty(stack)) {
        char stackHead = pop(stack, errorCode);
        enqueue(queue, stackHead, errorCode);
        enqueue(queue, ' ', errorCode);
    }
    deleteStack(&stack);
    
    char* postfixForm = queueToString(queue, strlen(inputString), errorCode);
    deleteQueue(&queue);
    if (*errorCode) {
        return NULL;
    }

    return postfixForm;
}