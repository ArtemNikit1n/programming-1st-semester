#include <stdlib.h>
#include <string.h>

int compareTwoString(const char* string1, const char* string2) {
    if (string1 == NULL || string2 == NULL) {
        if (string1 == NULL && string2 != NULL) {
            return -1;
        }
        if (string1 != NULL && string2 == NULL) {
            return 1;
        }
        if (string1 == NULL && string2 == NULL) {
            return 0;
        }
    }
    else {
        return strcmp(string1, string2);
    }
}