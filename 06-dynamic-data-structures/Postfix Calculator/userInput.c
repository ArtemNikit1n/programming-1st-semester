#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

bool checkUserInput(const char *string) {
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

char* readUserInput(bool* errorCode) {
    char* inputString = (char*)calloc(1, sizeof(char));
    if (inputString == NULL) {
        printf("������ ��������� ������\n");
        *errorCode = true;
        return NULL;
    }

    bool isInputIncorrect = false;
    do {
        isInputIncorrect = false;
        size_t bufferSize = 1;
        size_t lineLength = 0;
        while (true) {
            char oneCharacter = getchar();

            if (oneCharacter == '\n') {
                break;
            }

            if (lineLength + 1 >= bufferSize) {
                bufferSize *= 2;
                char* tmp = (char*)realloc(inputString, bufferSize * sizeof(char));
                if (tmp == NULL) {
                    printf("������ ��������� ������\n");
                    *errorCode = true;
                    return NULL;
                }
                inputString = tmp;
            }
            inputString[lineLength++] = oneCharacter;
        }

        inputString[lineLength] = '\0';
        if (!checkUserInput(inputString)) {
            isInputIncorrect = true;
            free(inputString);
            printf("��������� �� ������ ��������� �����, ���������� ��� ���\n");
            inputString = (char*)calloc(1, sizeof(char));
            if (inputString == NULL) {
                printf("������ ��������� ������\n");
                *errorCode = true;
                return NULL;
            }
        }
    } while (isInputIncorrect);
    return inputString;
}