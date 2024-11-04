#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "headerFile.h"
#include "time.h"
#include <assert.h>

long long fibonacciRecursively(int fibonacciIndex) {
    if (fibonacciIndex == 1) {
        return 1;
    }
    if (fibonacciIndex <= 0) {
        return 0;
    }
    return fibonacciRecursively(fibonacciIndex - 1) + fibonacciRecursively(fibonacciIndex - 2);
}

long long fibonaccIteratively(int fibonacciIndex) {
    long long fibonacciNumbers[100] = {0};
    fibonacciNumbers[1] = 1;

    for (int i = 2; i <= fibonacciIndex; ++i) {
        fibonacciNumbers[i] = fibonacciNumbers[i - 1] + fibonacciNumbers[i - 2];
    }
    return fibonacciNumbers[fibonacciIndex];
}

bool testIterativeAlgorithm() {
    bool test1Iteratively = fibonaccIteratively(5) == 5;
    bool test2Iteratively = fibonaccIteratively(30) == 832040;
    bool test3Iteratively = fibonaccIteratively(60) == 1548008755920;
    return test1Iteratively && test2Iteratively && test3Iteratively;
}

bool testRecursiveAlgorithm() {
    bool test1Recursively = fibonacciRecursively(5) == 5;
    bool test2Recursively = fibonacciRecursively(30) == 832040;
    return test1Recursively && test2Recursively;
}

void fibonacciNumbersTask() {
    char strFibonacciIndex[10];
    char *endptrFibonacciIndex;
    int fibonacciIndex = -1;

    assert(testIterativeAlgorithm());
    assert(testRecursiveAlgorithm());

    printf("Enter how many times you want to calculate the fibonacci number:\n");
    scanf("%s", strFibonacciIndex);
    fibonacciIndex = (int)strtol(strFibonacciIndex, &endptrFibonacciIndex, 10);
    assert(fibonacciIndex > 0 || *endptrFibonacciIndex == '\0');

    clock_t startFibonaccIteratively = clock();
    printf("\nIterative algorithm: %lld\n", fibonaccIteratively(fibonacciIndex));
    clock_t stopFibonaccIteratively = clock();
    double timeSpentFibonaccIteratively = (double)(stopFibonaccIteratively - startFibonaccIteratively) / CLOCKS_PER_SEC;
    printf("Time spent: %f seconds\n", timeSpentFibonaccIteratively);

    clock_t startFibonacciRecursively = clock();
    printf("Recursive algorithm: %lld\n", fibonacciRecursively(fibonacciIndex));
    clock_t stopFibonacciRecursively = clock();
    double timeSpentFibonacciRecursively = (double)(stopFibonacciRecursively - startFibonacciRecursively) / CLOCKS_PER_SEC;
    printf("Time spent: %f seconds\n", timeSpentFibonacciRecursively);
}