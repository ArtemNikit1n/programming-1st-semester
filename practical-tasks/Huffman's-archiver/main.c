#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"

typedef struct {
    bool code[256];
    int length;
} CodeEntry;

NodeValue createValue(char value, int frequency) {
    NodeValue nodeValue = { .value = value, .frequency = frequency };
    return nodeValue;
}

void printNode(Node* node, bool* errorCode) {
    NodeValue value = getValue(node, errorCode);
    printf("'%c': %d\n", value.value, value.frequency);
}

void fillOfArrayOfFrequencies(int arrayOfFrequencies[], char* string) {
    for (int i = 0; i < strlen(string); ++i) {
        unsigned char index = string[i];
        ++arrayOfFrequencies[index];
    }
}

int fillOfArrayOfNode(Node* arrayOfNode[], int arrayOfFrequencies[], bool* errorCode) {
    int notNull = 0;
    for (int i = 0; i < 256; ++i) {
        if (arrayOfFrequencies[i] == 0) {
            continue;
        }
        NodeValue value = createValue(i, arrayOfFrequencies[i]);
        arrayOfNode[i] = createNode(value, errorCode);
        ++notNull;
        if (*errorCode) {
            return 0;
        }
    }
    return notNull;
}

int getMinIndex(Node* arrayOfNode[], bool* errorCode) {
    int minIndexElement = -1;
    for (int i = 0; i < 256; ++i) {
        if (arrayOfNode[i] == NULL) {
            continue;
        }
        int frequency = getValue(arrayOfNode[i], errorCode).frequency;
        if (minIndexElement == -1) {
            minIndexElement = i;
            continue;
        }
        if (frequency < getValue(arrayOfNode[minIndexElement], errorCode).frequency) {
            minIndexElement = i;
        }
        if (*errorCode) {
            return -1;
        }
    }
    return minIndexElement;
}

Node* getRootNode(Node* arrayOfNode[], int notNull, bool* errorCode) {
    while (notNull > 1) {
        const int firstIndexMinElement = getMinIndex(arrayOfNode, errorCode);
        Node* firstMinNode = arrayOfNode[firstIndexMinElement];
        arrayOfNode[firstIndexMinElement] = NULL;
        if (*errorCode) {
            return NULL;
        }

        const int secondIndexMinElement = getMinIndex(arrayOfNode, errorCode);
        Node* secondMinNode = arrayOfNode[secondIndexMinElement];
        if (*errorCode) {
            return NULL;
        }

        const int newFrequency = getValue(firstMinNode, errorCode).frequency + getValue(secondMinNode, errorCode).frequency;
        Node* newNode = createNode(createValue('\0', newFrequency), errorCode);
        addLeftChild(newNode, firstMinNode, errorCode);
        addRightChild(newNode, secondMinNode, errorCode);
        arrayOfNode[secondIndexMinElement] = newNode;
        if (*errorCode) {
            return NULL;
        }

        --notNull;
    }

    Node* rootNode = NULL;
    for (int i = 0; i < 256; ++i) {
        if (arrayOfNode[i] == NULL) {
            continue;
        }
        rootNode = arrayOfNode[i];
        break;
    }

    return rootNode;
}

void writeToCodeTable(Node* currentNode, bool* currentCode, int currentCodeLength, CodeEntry codeTable[], bool* errorCode) {
    if (*errorCode) {
        return;
    }
    if (getLeftChild(currentNode, errorCode) == NULL && getRightChild(currentNode, errorCode) == NULL) {
        const unsigned char value = getValue(currentNode, errorCode).value;
        for (int i = 0; i < currentCodeLength; ++i) {
            codeTable[value].code[i] = currentCode[i];
        }
        codeTable[value].length = currentCodeLength;
        return;
    }
    currentCode[currentCodeLength] = false;
    writeToCodeTable(getLeftChild(currentNode, errorCode), currentCode, currentCodeLength + 1, codeTable, errorCode);

    currentCode[currentCodeLength] = true;
    writeToCodeTable(getRightChild(currentNode, errorCode), currentCode, currentCodeLength + 1, codeTable, errorCode);
}

void writeInt(FILE* file, int value) {
    char* array = &value;
    for (int i = 0; i < 4; ++i) {
        fputc(array[i], file);
    }
}
 
int readInt(FILE* file) {
    char array[4] = { '\0' };
    for (int i = 0; i < 4; ++i) {
        array[i] = fgetc(file);
    }
    int value = *((int*)array);
    return value;
}

void encode(const char* string) {
    int arrayOfFrequencies[256] = { 0 };
    bool errorCode = false;
    fillOfArrayOfFrequencies(arrayOfFrequencies, string);
    if (errorCode) {
        return errorCode;
    }

    Node* arrayOfNode[256] = { NULL };
    int notNull = fillOfArrayOfNode(arrayOfNode, arrayOfFrequencies, &errorCode);
    if (errorCode) {
        return errorCode;
    }

    Node* rootNode = getRootNode(arrayOfNode, notNull, &errorCode);
    if (errorCode) {
        return errorCode;
    }

    CodeEntry codeTable[256] = { 0 };
    bool currentCode[256] = { false };
    writeToCodeTable(rootNode, currentCode, 0, codeTable, &errorCode);
    if (errorCode) {
        return errorCode;
    }

    FILE* file = fopen("testFile.txt", "w");
    for (int i = 0; i < 256; ++i) {
        writeInt(file, arrayOfFrequencies[i]);
    }
    writeInt(file, strlen(string));
    bool buffer[8] = { false };
    int bufferIndex = 0;
    for (int i = 0; string[i] != '\0'; ++i) {
        CodeEntry entry = codeTable[string[i]];
        for (int j = 0; j < entry.length; ++j) {
            buffer[bufferIndex] = entry.code[j];
            ++bufferIndex;
            if (bufferIndex == 8) {
                unsigned char bufferValue = '\0';
                for (int k = 0; k < 8; ++k) {
                    bufferValue |= buffer[k] << k;
                }
                fputc(bufferValue, file);
                bufferIndex = 0;
            }
        }
    }
    fclose(file);
}

char* decode(const char* filename) {
    int array[256] = { '\0' };
    FILE* file = fopen(filename, "r");
    for (int i = 0; i < 256; ++i) {
        array[i] = readInt(file);
    }
    int length = readInt(file);
    Node* arrayOfNode[256] = { NULL };
    int errorCode = 0;
    int notNull = fillOfArrayOfNode(arrayOfNode, array, &errorCode);
    if (errorCode) {
        return errorCode;
    }

    Node* rootNode = getRootNode(arrayOfNode, notNull, &errorCode);
    if (errorCode) {
        return errorCode;
    }
    Node* currentNode = rootNode;
    bool buffer[8] = { false };
    char bufferValue = '\0';
    while (length > 0) {
        bufferValue = fgetc(file);
        for (int i = 0; i < 8; ++i) {
            buffer[i] = (bufferValue >> i) & 1;
        }
        int bufferIndex = 0;
        while (bufferIndex < 8) {
            if (getLeftChild(currentNode, &errorCode) == NULL) {
                printf("%c", getValue(currentNode, &errorCode).value);
                --length;
                currentNode = rootNode;
            }
            if (buffer[bufferIndex]) {
                currentNode = getRightChild(currentNode, &errorCode);
            }
            else {
                currentNode = getLeftChild(currentNode, &errorCode);
            }
            ++bufferIndex;
        }
    }
}

int main(void) {
    encode("aaaaabbbbbbdfsdferrr");
    decode("testFile.txt");
}
