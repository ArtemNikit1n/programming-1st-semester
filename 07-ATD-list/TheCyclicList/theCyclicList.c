
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../TheCyclicList/theCyclicList.h"

typedef struct ListElement* Position;

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
    return list->head == NULL;
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
    while (list->head != NULL) {
        if (list->head->next = list->head) {
            free(list->head);
            break;
        }
        ListElement* next = list->head->next;
        free(list->head);
        list->head = next;
    }
    free(list);
    *listDoublePointer = NULL;
}

Position calculateThePosition(List* list, int position, bool* errorCode) {
    if (position < 0) {
        *errorCode = true;
        return errorCode;
    }
    Position theSelectedElement = NULL;
    ListElement* head = list->head;
    for (int i = 1; i < position; ++i) {
        if (list->head == NULL) {
            *errorCode = true;
            return NULL;
        }
        list->head = list->head->next;
    }
    theSelectedElement = list->head;
    list->head = head;
    return theSelectedElement;
}

Value removeListElement(List* list, int position, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return true;
    }
    Position theSelectedElement = calculateThePosition(list, position, errorCode);
    if (*errorCode || NULL == theSelectedElement) {
        return errorCode;
    }
    if (theSelectedElement->next == theSelectedElement) {
        Value value = theSelectedElement->value;
        free(theSelectedElement);
        list->head = NULL;
        return value;
    }
    ListElement* temp = theSelectedElement->next;
    if (temp == NULL) {
        *errorCode = true;
        return NULL;
    } 
    Value value = temp->value;
    theSelectedElement->next = theSelectedElement->next->next;
    free(temp);
    if (list->head == NULL) {
        *errorCode = true;
        return NULL;
    }
    return value;
}

bool add(List* list, int position, Value value, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return true;
    }
    Position theSelectedElement = calculateThePosition(list, position, errorCode);
    if (*errorCode) {
        return errorCode;
    }
    ListElement* new = calloc(1, sizeof(ListElement));
    if (new == NULL) {
        *errorCode = true;
        return errorCode;
    }
    new->value = value;
    if (theSelectedElement == NULL) {
        list->head = new;
        new->next = new;
        return false;
    }
    ListElement* temp = theSelectedElement->next;
    theSelectedElement->next = new;
    new->next = temp;
    return false;
}
