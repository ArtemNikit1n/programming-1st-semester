#pragma once

#include "../list/list.h"

// Print all the values of the list.
void printList(List* list, int listLength, bool* errorCode);

// Sorts the list using insertion sorting.
void sortTheList(List* list, int listLength, bool* errorCode);