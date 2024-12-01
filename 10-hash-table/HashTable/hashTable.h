#pragma once

#include "../list/list.h"

// Builds a hash table with words from a file.
void buildHashTable(List* hashTable[], const char* fileName, bool* errorCode);

// Displaying words and their frequencies on the screen.
void printHashTable(List* hashTable[], bool* errorCode);