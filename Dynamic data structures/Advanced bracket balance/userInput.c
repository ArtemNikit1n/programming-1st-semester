#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <assert.h>

char* userInput() {
    char *inputString = (char *)calloc(1, sizeof(char));
    assert(inputString != NULL);
    size_t bufferSize = 1;
    size_t lineLength = 0;

    while (1) {
        char oneCharacter = getchar();

        if (oneCharacter == '\n') {
            break;
        }

        if (lineLength + 1 >= bufferSize) {
            bufferSize *= 2;
            char *tmp = (char*)realloc(inputString, bufferSize * sizeof(char));
            assert(tmp != NULL);
            inputString = tmp;
        }
        inputString[lineLength++] = oneCharacter;
    }

    inputString[lineLength] = '\0';
    return inputString;
}