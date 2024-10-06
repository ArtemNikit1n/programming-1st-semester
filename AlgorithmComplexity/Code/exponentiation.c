#include "headerFile.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

long double exponentiationLineTime(long long baseOfDegree, long exponent) {
    long double result = 1;
    bool negativeDegree = false;
    if (exponent < 0) {
        exponent *= -1;
        negativeDegree = true;
    }

    if (exponent == 0) {
        return result;
    }
    for (int i = 0; i < exponent; i++) {
        result *= baseOfDegree;
    }
    return negativeDegree ? (1.0 / result) : result;
}

long double exponentiationLogTime(long long baseOfDegree, long exponent) {
    long double result = 1;
    bool negativeDegree = false;
    if (exponent < 0) {
        exponent *= -1;
        negativeDegree = true;
    }

    if (exponent == 0) {
        return result;
    }
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= baseOfDegree;
        }
        exponent /= 2;
        baseOfDegree *= baseOfDegree;
    }

    return negativeDegree ? 1.0 / result : result;
}

bool testInputCorrectness(const char *endptrBaseOfDegree, const char *endptrExponent, const long long baseOfDegree) {
    if (baseOfDegree < 0) {
        printf("The base of a degree cannot be negative\n");
        return false;
    }
    if (*endptrBaseOfDegree != '\0' || *endptrExponent != '\0') {
        printf("Input error\n");
        return false;
    }
    return true;
}

bool testForCorrectnessOfCalculation() {
    const double epsilon = 0.000001;
    bool test1LineTime = exponentiationLineTime(5, 2) == 25;
    bool test2LineTime = exponentiationLineTime(50, 10) == 97656250000000000;
    bool test3LineTime = 0.000010 - epsilon < exponentiationLineTime(10, -5);
    bool test4LineTime = 0.000010 + epsilon > exponentiationLineTime(10, -5);

    bool test1LogTime = exponentiationLogTime(5, 2) == 25;
    bool test2LogTime = exponentiationLogTime(50, 10) == 97656250000000000;
    bool test3LogTime = 0.000010 - epsilon < exponentiationLogTime(10, -5);
    bool test4LogTime = 0.000010 + epsilon > exponentiationLogTime(10, -5);

    return (test1LineTime && test2LineTime && test3LineTime && test4LineTime && test1LogTime && test2LogTime && test3LogTime && test4LogTime);
}

void exponentiationTask() {
    char strBaseOfDegree[40];
    char strExponent[40];
    char *endptrBaseOfDegree;
    char *endptrExponent;

    long exponent = -1;
    long long baseOfDegree = -1;

    if (!testForCorrectnessOfCalculation()) {
        printf("Tests failed");
        return;
    }

    printf("Enter the base of the degree: ");
    scanf("%s", strBaseOfDegree);
    baseOfDegree = strtol(strBaseOfDegree, &endptrBaseOfDegree, 10);

    printf("Enter the exponent: ");
    scanf("%s", strExponent);
    exponent = strtol(strExponent, &endptrExponent, 10);

    if (!testInputCorrectness(endptrBaseOfDegree, endptrExponent, baseOfDegree)) {
        return;
    }

    long double resultExponentiationLogTime = exponentiationLogTime(baseOfDegree, exponent);
    long double resultExponentiationLineTime = exponentiationLineTime(baseOfDegree, exponent);
    assert(resultExponentiationLineTime > 0 && resultExponentiationLogTime > 0);

    printf("Result for logarithm: %Lf\n", resultExponentiationLogTime);
    printf("Result for line: %Lf\n", resultExponentiationLineTime);
}