#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

#include "dictionary.h"

void printTheBackgroundInformation() {
    printf(
        "0 - Exit\n"
        "1 - Add a value by key to the dictionary. If such a key already exists, the value is replaced with a new one.\n"
        "2 - Get the key value from the dictionary.\n"
        "3 - Check for the specified key.\n"
        "4 - Delete the specified key and its associated value from the dictionary.\n\n"
    );
}

char* getValueFromTheUser(bool* errorCode) {
    const int buffer = 101;
    char* value = calloc(buffer, sizeof(char));
    if (value == NULL) {
        *errorCode = true;
        return NULL;
    }
    scanf("%101s", value);
    while (strlen(value) == buffer) {
        printf("The string size is too large. Try again\n");
        while (getchar() != '\n');
        scanf("%101s", value);
    }
    return value;
}

<<<<<<< HEAD:08-trees/SearchTree/main.c
int getNumberFromTheUser(void) {
    int number = -1;
    int scanfReturns = scanf("%d", &number);
    while (scanfReturns != 1) {
        printf("Incorrect key has been entered, please try again:\n");
        while (getchar() != '\n');
        scanfReturns = scanf("%d", &number);
    }
    return number;
}

=======
>>>>>>> origin/09-self-balancing-trees:09-self-balancing-trees/AVL-tree/main.c
int getFunctionCodeFromTheUser(void) {
    int functionCode = -1;
    printTheBackgroundInformation();
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 4 || functionCode < 0 || scanfReturns != 1) {
        printf("Incorrect number. Please try again:\n");
        printTheBackgroundInformation();
<<<<<<< HEAD:08-trees/SearchTree/main.c
        while (getchar() != '\n');
=======
        while(getchar() != '\n');
>>>>>>> origin/09-self-balancing-trees:09-self-balancing-trees/AVL-tree/main.c
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

void launchAVLTree(int functionCode, bool* errorCode) {
    Node* root = NULL;
    bool isHeightChanged = false;

    while (functionCode != 0) {
        if (functionCode == 1) {
            printf("Enter the key:\n");
<<<<<<< HEAD:08-trees/SearchTree/main.c
            int key = getNumberFromTheUser();
            printf("Enter the value:\n");
            char* value = getValueFromTheUser(errorCode);
=======
            const char* key = getValueFromTheUser(errorCode);
>>>>>>> origin/09-self-balancing-trees:09-self-balancing-trees/AVL-tree/main.c
            if (*errorCode) {
                *errorCode = false;
                printf("Memory allocation error. Try again\n");
                functionCode = getFunctionCodeFromTheUser();
<<<<<<< HEAD:08-trees/SearchTree/main.c
=======
                continue;
            }
            printf("Enter the value:\n");
            const char* value = getValueFromTheUser(errorCode);
            if (*errorCode) {
                free(key);
                *errorCode = false;
                printf("Memory allocation error. Try again\n");
                functionCode = getFunctionCodeFromTheUser();
>>>>>>> origin/09-self-balancing-trees:09-self-balancing-trees/AVL-tree/main.c
                continue;
            }

            if (root == NULL) {
                root = createTree(key, value, errorCode);
                if (*errorCode) {
<<<<<<< HEAD:08-trees/SearchTree/main.c
=======
                    free(key);
>>>>>>> origin/09-self-balancing-trees:09-self-balancing-trees/AVL-tree/main.c
                    free(value);
                    *errorCode = false;
                    printf("Memory allocation error. Try again\n");
                    functionCode = getFunctionCodeFromTheUser();
                    continue;
                }
                functionCode = getFunctionCodeFromTheUser();
                continue;
            }
<<<<<<< HEAD:08-trees/SearchTree/main.c
            root = addNode(root, key, value, errorCode);
            free(value);
=======
            root = addNode(root, key, value, &isHeightChanged, errorCode);
            if (*errorCode) {
                free(key);
                free(value);
                *errorCode = false;
                printf("Error. Try again later\n");
                functionCode = getFunctionCodeFromTheUser();
                continue;
            }
            free(key);
            free(value);
            isHeightChanged = false;
        }
        if (functionCode == 2) {
            printf("Enter the key:\n");
            const char* theKeyForTheSearch = getValueFromTheUser(errorCode);
>>>>>>> origin/09-self-balancing-trees:09-self-balancing-trees/AVL-tree/main.c
            if (*errorCode) {
                *errorCode = false;
                printf("Error. Try again later\n");
                functionCode = getFunctionCodeFromTheUser();
                continue;
            }
<<<<<<< HEAD:08-trees/SearchTree/main.c
        }
        if (functionCode == 2) {
            printf("Enter the key:\n");
            int theKeyForTheSearch = getNumberFromTheUser();
            const char* theFoundString = searchByKey(root, theKeyForTheSearch);
=======
            const char* theFoundString = searchByKey(root, theKeyForTheSearch);
            free(theKeyForTheSearch);
>>>>>>> origin/09-self-balancing-trees:09-self-balancing-trees/AVL-tree/main.c
            if (theFoundString != NULL) {
                printf("%s\n", theFoundString);
            }
            else {
                printf("The key was not found\n");
            }
        }
        if (functionCode == 3) {
            printf("Enter the key:\n");
<<<<<<< HEAD:08-trees/SearchTree/main.c
            int keyForSearch = getNumberFromTheUser();
            const char* theFoundString = searchByKey(root, keyForSearch);
=======
            const char* keyForSearch = getValueFromTheUser(errorCode);
            if (*errorCode) {
                *errorCode = false;
                printf("Error. Try again later\n");
                functionCode = getFunctionCodeFromTheUser();
                continue;
            }
            const char* theFoundString = searchByKey(root, keyForSearch);
            free(keyForSearch);
>>>>>>> origin/09-self-balancing-trees:09-self-balancing-trees/AVL-tree/main.c
            if (theFoundString != NULL) {
                printf("The key was found\n");
            }
            else {
                printf("The key was not found\n");
            }
        }
        if (functionCode == 4) {
            printf("Enter the key:\n");
<<<<<<< HEAD:08-trees/SearchTree/main.c
            int theKeyToDelete = getNumberFromTheUser();

            root = deleteNode(root, theKeyToDelete, errorCode);
=======
            const char* theKeyToDelete = getValueFromTheUser(errorCode);
>>>>>>> origin/09-self-balancing-trees:09-self-balancing-trees/AVL-tree/main.c
            if (*errorCode) {
                *errorCode = false;
                printf("Error. Try again later\n");
                functionCode = getFunctionCodeFromTheUser();
                continue;
            }
<<<<<<< HEAD:08-trees/SearchTree/main.c
=======

            root = deleteNode(root, theKeyToDelete, &isHeightChanged, errorCode);
            free(theKeyToDelete);
            if (*errorCode) {
                *errorCode = false;
                printf("Error. Try again later\n");
                functionCode = getFunctionCodeFromTheUser();
                continue;
            }
            isHeightChanged = false;
>>>>>>> origin/09-self-balancing-trees:09-self-balancing-trees/AVL-tree/main.c
            printf("The value has been deleted!\n");
        }
        functionCode = getFunctionCodeFromTheUser();
    }
}

int main(void) {
    bool errorCode = false;

    runTheDictionaryTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

<<<<<<< HEAD:08-trees/SearchTree/main.c
    callTheFunction(getFunctionCodeFromTheUser(), &errorCode);
=======
    launchAVLTree(getFunctionCodeFromTheUser(), &errorCode);

>>>>>>> origin/09-self-balancing-trees:09-self-balancing-trees/AVL-tree/main.c
    return errorCode;
}