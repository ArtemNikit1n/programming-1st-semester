#pragma once

#include "../list/list.h"

// Builds a hash table with words from a file.
// The function returns an array of three numbers, in which the first is the hash table fill factor,
// the second is the average length of the list and the third is the maximum length of the list.
float* buildHashTable(List* hashTable[], const char* fileName, int *hashTableSize, bool* errorCode);

// Displaying words and their frequencies on the screen.
void printHashTable(List* hashTable[], int* hashTableSize, bool* errorCode);