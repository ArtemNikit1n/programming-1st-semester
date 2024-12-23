#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <errno.h>

#define SIZEOF 32

bool comparingTwoArrays(bool firstArray[], bool secondArray[], int arrayLength) {
    bool errorCode = true;
    for (int i = 0; i < arrayLength; ++i) {
        if (firstArray[i] != secondArray[i]) {
            errorCode = false;
            break;
        }
    }
    return errorCode;
}

void printBoolArray(bool boolArray[], int boolArrayLength) {
    for (int i = 0; i < boolArrayLength; ++i) {
        printf("%d", boolArray[i]);
    }
}

void binarySum(bool binaryFirstNumber[], bool binarySecondNumber[], bool binarySumArray[]) {
    bool theAdditionalTerm = 0;
    for (int i = SIZEOF - 1; i >= 0; --i) {
        bool oneAndZero = (binaryFirstNumber[i] && !binarySecondNumber[i]) || (!binaryFirstNumber[i] && binarySecondNumber[i]);
        if (!binaryFirstNumber[i] && !binarySecondNumber[i]) {
            if (theAdditionalTerm) {
                theAdditionalTerm = 0;
                binarySumArray[i] = 1;
            } 
            else {
                binarySumArray[i] = 0;
            }
        }
        if (binaryFirstNumber[i] && binarySecondNumber[i]) {
            if (theAdditionalTerm) {
                theAdditionalTerm = 1;
                binarySumArray[i] = 1;
            }
            else {
                theAdditionalTerm = 1;
                binarySumArray[i] = 0;
            }
        }
        if (oneAndZero) {
            if (theAdditionalTerm) {
                theAdditionalTerm = 1;
                binarySumArray[i] = 0;
            }
            else {
                binarySumArray[i] = 1;
            }
        }
    }
}

int conversionToDecimal(bool binaryNumber[]) {
    int decimalNumber = 0;

    int k = 1;
    for (int i = SIZEOF - 1; i >= 0; --i) {
        decimalNumber += binaryNumber[i] * k;
        k *= 2;
    }
    return decimalNumber;
}

void getBinaryNumber(int decimalNumber, bool binaryNumber[]) {
    for (int i = 0; i < SIZEOF; ++i) {
        if ((decimalNumber) & (1 << i)) {
            binaryNumber[SIZEOF - 1 - i] = 1;
        } else {
            binaryNumber[SIZEOF - 1 - i] = 0;
        }
    }
}

void userInput(int *firstNumber, int *secondNumber, bool *errorCode) {
    char strFirstNumber[100];
    char strSecondNumber[100];
    char* endptrFirstNumber = NULL;
    char* endptrSecondNumber = NULL;
    errno = 0;

    setlocale(LC_ALL, "Rus");

    printf("Введите первое число:\n");
    scanf("%s", strFirstNumber); 
    *firstNumber = (int)strtol(strFirstNumber, &endptrFirstNumber, 10);

    printf("Введите второе число:\n");
    scanf("%s", strSecondNumber);
    *secondNumber = (int)strtol(strSecondNumber, &endptrSecondNumber, 10);

    if (errno == ERANGE) {
        printf("Ошибка ввода");
        *errorCode = true;
    }

    if (*endptrFirstNumber != '\0' || *endptrSecondNumber != '\0') {
        printf("Ошибка ввода");
        *errorCode = true;
    }
}

void checkingTheAmountForStackOverflow(int firstNumber, int secondNumber, bool *errorCode) {
    if (firstNumber < 0 && secondNumber < 0 && abs(firstNumber) > INT_MAX + (secondNumber + 1)) {
        printf("Переполнение стека");
        *errorCode = true;
    }
    if (firstNumber > 0 && secondNumber > 0 && firstNumber > INT_MAX - secondNumber) {
        printf("Переполнение стека");
        *errorCode = true;
    }
}

bool testComparingTwoArrays() {
    bool firstArray[6] = { 1, 0, 0, 1, 0, 1 };
    bool secondArray[6] = { 0, 1, 1, 1, 0, 0 };

    return !comparingTwoArrays(firstArray, secondArray, 6) && comparingTwoArrays(firstArray, firstArray, 6);
}

bool testGetBinaryNumber() {
    int positiveNumber = 2048;
    int negativeNumber = -1025;
    bool positiveNumberArray[SIZEOF] = { 0 };
    positiveNumberArray[20] = 1;
    bool negativeNumberArray[SIZEOF] = { 0 };
    for (int i = 0; i < 32; i++) {
        negativeNumberArray[i] = 1;
    }
    negativeNumberArray[21] = 0;
    bool theResultIsForThePositive[SIZEOF] = { 0 };
    bool theResultIsForTheNegative[SIZEOF] = { 0 };
    getBinaryNumber(positiveNumber, theResultIsForThePositive);
    getBinaryNumber(negativeNumber, theResultIsForTheNegative);

    return comparingTwoArrays(positiveNumberArray, theResultIsForThePositive, SIZEOF) && comparingTwoArrays(negativeNumberArray, theResultIsForTheNegative, SIZEOF);
}

bool testBinarySum() {
    bool theFirstSummand[SIZEOF] = { 0 };
    for (int i = 1; i < SIZEOF; i++) {
        theFirstSummand[i] = 1;
    }
    bool theSecondSummand[SIZEOF] = { 0 };
    for (int i = 0; i < SIZEOF; i++) {
        theSecondSummand[i] = 1;
    }
    bool expectedResult[SIZEOF] = { 0 };
    for (int i = 1; i < SIZEOF - 1; i++) {
        expectedResult[i] = 1;
    }

    bool result[SIZEOF] = { 0 };
    binarySum(theFirstSummand, theSecondSummand, result);
    return comparingTwoArrays(result, expectedResult, SIZEOF);
}

bool testConversionToDecimal() {
    bool positiveNumberArray[SIZEOF] = { 0 };
    positiveNumberArray[20] = 1;
    bool negativeNumberArray[SIZEOF] = { 0 };
    for (int i = 0; i < SIZEOF; i++) {
        negativeNumberArray[i] = 1;
    }
    negativeNumberArray[21] = 0;
    return conversionToDecimal(positiveNumberArray) == 2048 && conversionToDecimal(negativeNumberArray) == -1025;
}

int main(void) {
    int firstNumber = -1;
    int secondNumber = -1;
    int decimalSumNumber = -1;
    bool binaryFirstNumber[SIZEOF] = { 0 };
    bool binarySecondNumber[SIZEOF] = { 0 };
    bool binarySumArray[SIZEOF] = { 0 };

    bool errorCode = false;

    setlocale(LC_ALL, "Rus");

    if (!testComparingTwoArrays()) {
        printf("Тест comparingTwoArrays не пройден\n");
        errorCode = true;
        return errorCode;
    }

    if (!testGetBinaryNumber()) {
        printf("Тест getBinaryNumber не пройден\n");
        errorCode = true;
        return errorCode;
    }

    if (!testBinarySum()) {
        printf("Тест binarySum не пройден\n");
        errorCode = true;
        return errorCode;
    }

    if (!testConversionToDecimal()) {
        printf("Тест conversionToDecimal не пройден\n");
        errorCode = true;
        return errorCode;
    }

    userInput(&firstNumber, &secondNumber, &errorCode);
    if (errorCode) {
        return errorCode;
    }
    checkingTheAmountForStackOverflow(firstNumber, secondNumber, &errorCode);
    if (errorCode) {
        return errorCode;
    }

    getBinaryNumber(firstNumber, binaryFirstNumber);
    getBinaryNumber(secondNumber, binarySecondNumber);
    binarySum(binaryFirstNumber, binarySecondNumber, binarySumArray);

    printf("Двоичное представление первого числа в дополнительном коде:\n");
    printBoolArray(binaryFirstNumber, SIZEOF);
    printf("\nДвоичное представление второго числа в дополнительном коде:\n");
    printBoolArray(binarySecondNumber, SIZEOF);
    printf("\nДвоичная сумма:\n");
    printBoolArray(binarySumArray, SIZEOF);
    decimalSumNumber = conversionToDecimal(binarySumArray);
    printf("\nДесятичная сумма:\n%d", decimalSumNumber);

    return errorCode;
}