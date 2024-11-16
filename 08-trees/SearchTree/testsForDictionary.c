#include <stdio.h>
#include <stdbool.h>

#include "dictionary.h"
#include "../Tree/tree.h"

bool testFindValueByTheKeyAndAddToTheDictionary(bool* errorCode) {
    Node* root = createNode(createNodeValue(1, "a"), errorCode);
    addToTheDictionary(root, 5, "b", errorCode);
    addToTheDictionary(root, 3, "c", errorCode);
    addToTheDictionary(root, 10, "f", errorCode);
    addToTheDictionary(root, -5, "d", errorCode);
    addToTheDictionary(root, -3, "e", errorCode);

    bool test1 = findValueByTheKey(root, 3, errorCode) == "c";
    bool test2 = findValueByTheKey(root, 1, errorCode) == "a";
    bool test3 = findValueByTheKey(root, -3, errorCode) == "e";
    bool test4 = findValueByTheKey(root, 0, errorCode) == NULL;
    disposeNode(&root);

    return test1 && test2 && test3 && test4;
}

void runTheDictionaryTests(bool* errorCode) {
    if (!testFindValueByTheKeyAndAddToTheDictionary(errorCode)) {
        printf("Тест testFindValueByTheKeyAndAddToTheDictionary не пройден\n");
        if (*errorCode) {
            printf("Код ошибки: 1\n");
            return;
        }
        printf("Код ошибки: 0\n");
        *errorCode = true;
        return;
    }
}