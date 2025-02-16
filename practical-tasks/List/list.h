#pragma once

typedef struct List List;

void deleteList(List **listDoublePointer);

typedef struct ListElement* Posithion;

List * createList(bool *errorCode);

void add(List* list, struct ListElement* position, int value);

void popList(List* list, struct ListElement* position, bool* errorCode);

