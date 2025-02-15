#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../listForMergeSort/list.h"

typedef struct ListElement {
    Value value;
    struct ListElement* next;
} ListElement;

struct List {
    ListElement* head;
};

bool listIsEmpty(List* list, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return true;
    }
    return list->head->next == NULL;
}

List* createList(bool* errorCode) {
    ListElement* guardian = calloc(1, sizeof(ListElement));
    if (guardian == NULL) {
        *errorCode = true;
        return NULL;
    }
    List* list = calloc(1, sizeof(List));
    if (list == NULL) {
        free(guardian);
        *errorCode = true;
        return NULL;
    }
    list->head = guardian;
    return list;
}

void deleteList(List** listDoublePointer) {
    List* list = *listDoublePointer;
    if (list == NULL) {
        return;
    }
    while (list->head != NULL) {
        ListElement* next = list->head->next;
        free(list->head);
        list->head = next;
    }
    free(list);
    *listDoublePointer = NULL;
}

Value removeListElement(List* list, Position position, bool* errorCode) {
    Value emptyValue = { .name = NULL, .phone = NULL };

    if (list == NULL || NULL == position) {
        *errorCode = true;
        return emptyValue;
    }
    if (list->head == NULL) {
        *errorCode = true;
        return emptyValue;
    }

    ListElement* temp = position->next;
    if (temp == NULL) {
        *errorCode = true;
        return emptyValue;
    }
    Value value = temp->value;
    position->next = position->next->next;
    free(temp);

    return value;
}

Position add(List* list, Position position, Value value, bool* errorCode) {
    if (list == NULL || position == NULL) {
        *errorCode = true;
        return NULL;
    }

    ListElement* new = calloc(1, sizeof(ListElement));
    if (new == NULL) {
        *errorCode = true;
        return NULL;
    }
    new->value = value;

    ListElement* temp = position->next;
    position->next = new;
    new->next = temp;
    return new;
}

Position first(List* list, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    return list->head;
}

Position next(Position position, bool* errorCode) {
    if (position == NULL) {
        *errorCode = true;
        return NULL;
    }
    return position->next;
}

Value getValue(Position position, bool* errorCode) {
    if (position == NULL) {
        *errorCode = true;
        Value emptyValue = { .name = NULL, .phone = NULL };
        return emptyValue;
    }
    return position->value;
}

Value setValue(Position position, Value value, bool* errorCode) {
    if (position == NULL) {
        *errorCode = true;
        Value emptyValue = { .name = NULL, .phone = NULL };
        return emptyValue;
    }
    position->value = value;
}

Position last(List* list, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    Position i = first(list, errorCode);
    while (next(i, errorCode) != NULL) {
        i = next(i, errorCode);
        if (*errorCode) {
            return NULL;
        }
    }
    return i;
}
