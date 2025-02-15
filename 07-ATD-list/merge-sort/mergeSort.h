#pragma once

#include "../listForMergeSort/list.h"
#include <stdbool.h>

// Sorts a list with elements of the char* type.
void mergeSort(List* list, SortingCriteria criteria, bool* errorCode);