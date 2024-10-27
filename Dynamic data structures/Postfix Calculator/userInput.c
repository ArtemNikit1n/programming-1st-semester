#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

bool checkingUserInput(const char *string) {
    const char correctCharacters[] = "0123456789+-*/ ";
    int i = 0;

    if (NULL == string) {
        return false;
    }

    while (string[i] != '\0') {
        if (NULL == strchr(correctCharacters, string[i])) {
            return false;
        }
        ++i;
    }

    return true;
}

char* userInput() {
    char* inputString = (char*)calloc(1, sizeof(char));
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
            char* tmp = (char*)realloc(inputString, bufferSize * sizeof(char));
            assert(tmp != NULL);
            inputString = tmp;
        }
        inputString[lineLength++] = oneCharacter;
    }

    inputString[lineLength] = '\0';
    if (checkingUserInput(inputString)) {
        return inputString;
    } else {
        printf("Выражение не должно содержать буквы, попробуйте ещё раз\n");
        free(inputString);
        userInput();
    }
}