#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

void swap(int* first, int* second) {
    if (*first == *second) {
        return;
    }
    *first ^= *second;
    *second ^= *first;
    *first ^= *second;
}

bool isSorted(int array[], int arrayLehgth) {
    for (int i = 0; i < arrayLehgth - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

void shuffleTheArray(int array[], int arrayLehgth) {
    for (int i = arrayLehgth - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&array[i], &array[j]);
    }
    return;
}

void sortByMonkeySorting(int array[], int arrayLehgth) {
    while (!isSorted(array, arrayLehgth)) {
        shuffleTheArray(array, arrayLehgth);
    }
    return;
}

bool testSortByMonkeySorting() {
    int arrayLehgth = 6;
    int testArray1[] = { 10, 4213, 8, 111122222, 9, -231 };
    int testArray2[] = { 1, 2, 3, 4, 5, 6 };
    int testArray3[] = { -1, -1, -1, -1, -1, -1 };
    int testArray4[] = { -1, -2, -3, -4, -5, -6 };

    sortByMonkeySorting(testArray1, arrayLehgth);
    sortByMonkeySorting(testArray2, arrayLehgth);
    sortByMonkeySorting(testArray3, arrayLehgth);
    sortByMonkeySorting(testArray4, arrayLehgth);

    bool test1 = isSorted(testArray1, arrayLehgth);
    bool test2 = isSorted(testArray2, arrayLehgth);
    bool test3 = isSorted(testArray3, arrayLehgth);
    bool test4 = isSorted(testArray4, arrayLehgth);

    return test1 && test2 && test3 && test4;
}

void task2(bool* errorCode) {
    srand(time(NULL));
    if (!testSortByMonkeySorting()) {
        printf("Тесты sortByMonkeySorting не пройдены");
        *errorCode = true;
        return;
    }
    printf("Тесты sortByMonkeySorting пройдены\n");
}