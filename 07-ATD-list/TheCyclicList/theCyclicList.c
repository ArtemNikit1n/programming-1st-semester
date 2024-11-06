
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../TheCyclicList/theCyclicList.h"

typedef struct ListElement {
    Value value;
    struct ListElement* next;
} ListElement;

struct List {
    ListElement* first;
    ListElement* last;
};

bool listIsEmpty(List* list, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return true;
    }
    return list->last == NULL;
}

List* createList(bool* errorCode) {
    List* list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    return list;
}

void deleteList(List** listDoublePointer) {
    List* list = *listDoublePointer;
    if (list == NULL) {
        return;
    }
    while (list->first != NULL) {
        if (list->first->next = list->first) {
            free(list->first);
            break;
        }
        ListElement* next = list->first->next;
        free(list->first);
        list->first = next;
    }
    free(list);
    *listDoublePointer = NULL;
}

Value removeListElement(List* list, Position position, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return true;
    }
    if (list->first == list->last) {
        Value value = position->value;
        free(position);
        list->first = NULL;
        list->last = NULL;
        return value;
    }
    ListElement* temp = position;
    if (list->first == position && list->first->next != position) {
        list->first = list->first->next;
    }
    //if (list->last == position && list->last->next != position) {
    //    list->last = 
    //}
    if (temp == NULL) {
        *errorCode = true;
        return NULL;
    } 
    Value value = position->value;
    position = position->next;
    free(temp);
    if (list->first == NULL) {
        *errorCode = true;
        return NULL;
    }
    return value;
}

void add(List* list, Position position, Value value, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return;
    }
    ListElement* new = calloc(1, sizeof(ListElement));
    if (new == NULL) {
        *errorCode = true;
        return;
    }
    new->value = value;
    if (position == NULL) {
        list->first = new;
        list->last = new;
        new->next = new;
        return;
    }
    //if (list->first == position) {
    //    new->next = position;
    //    list->last->next = new;
    //    list->first = new;
    //    return;
    //}
    if (list->last == position) {
        new->next = list->first;
        position->next = new;
        list->last = new;
        return;
    }
    ListElement* temp = position->next;
    position->next = new;
    new->next = temp;
}

Position first(List* list, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    return list->first;
}

Position last(List* list, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    return list->last;
}

Position next(Position position, bool *errorCode) {
    if (position == NULL) {
        *errorCode = true;
        return NULL;
    }
    if (position->next == NULL) {
        *errorCode = true;
        return NULL;
    }
    return position->next;
}

Value getValue(Position position, bool *errorCode) {
    if (position == NULL) {
        *errorCode = true;
        return 0;
    }
    return position->value;
}
