#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

#include "avlTree.h"
#include "avlTreeTests.h"

void printTheBackgroundInformation() {
    printf(
        "0 – Выход\n"
        "1 – Äîáàâèòü çíà÷åíèå â ñëîâàðü\n"
        "2 – Âûâåñòè çíà÷åíèå ïî êëþ÷ó\n"
        "3 – Ïðîâåðèòü íàëè÷èå çàäàííîãî êëþ÷à â ñëîâàðå\n"
        "4 - Óäàëèòü çàäàííûé êëþ÷ è ñâÿçàííîå ñ íèì çíà÷åíèå èç ñëîâàðÿ\n\n"
    );
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char* getValueFromTheUser(bool* errorCode) {
    int buffer = 101;
    char* value = calloc(buffer, sizeof(char));
    if (value == NULL) {
        *errorCode = true;
        return NULL;
    }
    printf("Ââåäèòå çíà÷åíèå:\n");
    scanf("%101s", value);
    while (strlen(value) == buffer) {
        printf("Ââåäåíà ñëèøêîì äëèííàÿ ñòðîêà, ïîïðîáóéòå åù¸ ðàç\n");
        clearBuffer();
        scanf("%101s", value);
    }
    return value;
}

int getTheFunctionCodeFromTheUser(void) {
    int functionCode = -1;
    printTheBackgroundInformation();
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 4 || functionCode < 0 || scanfReturns != 1) {
        printf("Ââåä¸í íåêîððåêòíûé íîìåð êîìàíäû, ïîïðîáóéòå åù¸ ðàç:\n");
        printTheBackgroundInformation();
        clearBuffer();
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

void callTheFunction(int functionCode, bool* errorCode) {
    Node* root = NULL;
    while (functionCode != 0) {
        if (functionCode == 1) {
            printf("Ââåäèòå êëþ÷:\n");
            const char* key = getValueFromTheUser(errorCode);
            const char* value = getValueFromTheUser(errorCode);
            if (*errorCode) {
                *errorCode = false;
                printf("Îøèáêà âûäåëåíèÿ ïàìÿòè, ïîïðîáóéòå â äðóãîé ðàç\n");
                functionCode = getTheFunctionCodeFromTheUser();
                continue;
            }

            if (root == NULL) {
                root = createTree(key, value, errorCode);
                if (*errorCode) {
                    *errorCode = false;
                    free(value);
                    printf("Îøèáêà âûäåëåíèÿ ïàìÿòè, ïîïðîáóéòå â äðóãîé ðàç\n");
                    functionCode = getTheFunctionCodeFromTheUser();
                    continue;
                }
                functionCode = getTheFunctionCodeFromTheUser();
                continue;
            }
            addNode(root, key, value, errorCode);
        }
        if (functionCode == 2) {
            printf("Ââåäèòå êëþ÷:\n");
            const char* theKeyForTheSearch = getValueFromTheUser(errorCode);
            const char* theFoundString = searchByKey(root, theKeyForTheSearch);
            if (*errorCode) {
                *errorCode = false;
                printf("Îøèáêà ïîèñêà, ïîïðîáóéòå â äðóãîé ðàç\n");
                functionCode = getTheFunctionCodeFromTheUser();
                continue;
            }
            printf("%s\n", theFoundString);
        }
        if (functionCode == 3) {
            printf("Ââåäèòå êëþ÷:\n");
            const char* theKeyForTheSearch = getValueFromTheUser(errorCode);
            const char* theFoundString = searchByKey(root, theKeyForTheSearch);
            if (*errorCode) {
                *errorCode = false;
                printf("Îøèáêà ïîèñêà, ïîïðîáóéòå â äðóãîé ðàç\n");
                functionCode = getTheFunctionCodeFromTheUser();
                continue;
            }
            if (theFoundString != NULL) {
                printf("Êëþ÷ íàéäåí\n");
            }
            else {
                printf("Êëþ÷ íå íàéäåí\n");
            }
        }
        if (functionCode == 4) {
            printf("Ââåäèòå êëþ÷:\n");
            const char* theKeyToDelete = getValueFromTheUser(errorCode);
            bool isHeightChanged = false;
            root = deleteNode(root, theKeyToDelete, &isHeightChanged, errorCode);
            isHeightChanged = false;
        }
        functionCode = getTheFunctionCodeFromTheUser();
    }
}

int main(void) {
    bool errorCode = false;
    runAVLTreeTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    callTheFunction(getTheFunctionCodeFromTheUser(), &errorCode);

    return errorCode;
}