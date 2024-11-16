#pragma once

#include "../Tree/tree.h"

void addToTheDictionary(Node* node, const int key, const char* value, bool* errorCode);

char* findValueByTheKey(Node* node, const int key, bool* errorCode);