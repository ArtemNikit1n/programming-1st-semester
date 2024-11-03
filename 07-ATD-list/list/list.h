#pragma once

typedef int Value;

typedef struct List List;

// Returns true if the list is empty.
bool listIsEmpty(List* list, bool* errorCode);

// Deletes the list.
void deleteList(List** listDoublePointer);

// Creates a list together with the guard.
List* createList(bool* errorCode);

// Adds a new element to the specified location.
bool add(List* list, int position, Value value, bool* errorCode);

// Deletes an element from the specified location.
Value remove(List* list, int position, bool* errorCode);