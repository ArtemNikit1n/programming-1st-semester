#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

typedef struct ListElement {
    int value;
    struct ListElement* next;
} ListElement;

struct List {
    ListElement* head;
};

void deleteList(List** listDoublePointer) {
    List* stack = *listDoublePointer;
    while (stack->head != NULL) {
        ListElement* next = stack->head->next;
        free(stack->head);
        stack->head = next;
    }
    free(stack);
    *listDoublePointer = NULL;
}

void pop(List * list, ListElement * position, int * errorCode) {
    ListElement * temp = position->next;
    position->next = position->next->next;
    free(temp);
}

List* createList(bool* errorCode) {
    ListElement* guardian = calloc(1, sizeof(ListElement));
    if (guardian == NULL) {
        *errorCode = true;
        return NULL;
    }
    List* list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    list->head = guardian;
    return list;
}

void add(List* list, Posithion position, int value) {
    ListElement* new = calloc(1, sizeof(ListElement));
    if (new == NULL) {
        return;
    }
    ListElement* temp = position->next->next;
    position->next = new;
    new->next = temp;
}