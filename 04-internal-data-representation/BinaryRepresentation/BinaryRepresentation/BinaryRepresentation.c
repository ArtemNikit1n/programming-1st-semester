#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <errno.h>

#define SIZE_OF_NUMBER 32

bool areArraysEqual(bool firstArray[], bool secondArray[], int arrayLength) {
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
    bool theAdditionalTerm = false;
    for (int i = SIZE_OF_NUMBER - 1; i >= 0; --i) {
        if (!binaryFirstNumber[i] && !binarySecondNumber[i]) {
            if (theAdditionalTerm) {
                theAdditionalTerm = false;
                binarySumArray[i] = true;
            }
            else {
                binarySumArray[i] = false;
            }
        }
        if (binaryFirstNumber[i] && binarySecondNumber[i]) {
            if (theAdditionalTerm) {
                theAdditionalTerm = true;
                binarySumArray[i] = true;
            }
            else {
                theAdditionalTerm = true;
                binarySumArray[i] = false;
            }
        }
        if (binaryFirstNumber[i] ^ binarySecondNumber[i]) {
            if (theAdditionalTerm) {
                theAdditionalTerm = true;
                binarySumArray[i] = false;
            }
            else {
                binarySumArray[i] = true;
            }
        }
    }
}

int conversionToDecimal(bool binaryNumber[]) {
    int decimalNumber = 0;

    int k = 1;
    for (int i = SIZE_OF_NUMBER - 1; i >= 0; --i) {
        decimalNumber += binaryNumber[i] * k;
        k *= 2;
    }
    return decimalNumber;
}

void getBinaryNumber(int decimalNumber, bool binaryNumber[]) {
    for (int i = 0; i < SIZE_OF_NUMBER; ++i) {
        binaryNumber[SIZE_OF_NUMBER - 1 - i] = (decimalNumber & (1 << i)) != 0;
    }
}

int getIntValueFromUser(void) {
    int functionCode = -1;
    int scanfReturns = scanf("%d", &functionCode);
    while (scanfReturns != 1) {
        printf("Ошибка ввода. Попробуйте ещё раз:\n");
        while (getchar() != '\n');
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

void readUserInput(int *firstNumber, int *secondNumber, bool *errorCode) {
    printf("Введите первое число:\n");
    *firstNumber = getIntValueFromUser();

    printf("Введите второе число:\n");
    *secondNumber = getIntValueFromUser();
}

bool testComparingTwoArrays() {
    bool firstArray[6] = { 1, 0, 0, 1, 0, 1 };
    bool secondArray[6] = { 0, 1, 1, 1, 0, 0 };

    return !areArraysEqual(firstArray, secondArray, 6) && areArraysEqual(firstArray, firstArray, 6);
}

bool testGetBinaryNumber() {
    int positiveNumber = 2048;
    int negativeNumber = -1025;
    bool positiveNumberArray[SIZE_OF_NUMBER] = { 0 };
    positiveNumberArray[20] = 1;
    bool negativeNumberArray[SIZE_OF_NUMBER] = { 0 };
    for (int i = 0; i < 32; i++) {
        negativeNumberArray[i] = 1;
    }
    negativeNumberArray[21] = 0;
    bool theResultIsForThePositive[SIZE_OF_NUMBER] = { 0 };
    bool theResultIsForTheNegative[SIZE_OF_NUMBER] = { 0 };
    getBinaryNumber(positiveNumber, theResultIsForThePositive);
    getBinaryNumber(negativeNumber, theResultIsForTheNegative);

    return areArraysEqual(positiveNumberArray, theResultIsForThePositive, SIZE_OF_NUMBER) && areArraysEqual(negativeNumberArray, theResultIsForTheNegative, SIZE_OF_NUMBER);
}

bool testBinarySum() {
    bool theFirstSummand[SIZE_OF_NUMBER] = { 0 };
    for (int i = 1; i < SIZE_OF_NUMBER; i++) {
        theFirstSummand[i] = 1;
    }
    bool theSecondSummand[SIZE_OF_NUMBER] = { 0 };
    for (int i = 0; i < SIZE_OF_NUMBER; i++) {
        theSecondSummand[i] = 1;
    }
    bool expectedResult[SIZE_OF_NUMBER] = { 0 };
    for (int i = 1; i < SIZE_OF_NUMBER - 1; i++) {
        expectedResult[i] = 1;
    }

    bool result[SIZE_OF_NUMBER] = { 0 };
    binarySum(theFirstSummand, theSecondSummand, result);
    return areArraysEqual(result, expectedResult, SIZE_OF_NUMBER);
}

bool testConversionToDecimal() {
    bool positiveNumberArray[SIZE_OF_NUMBER] = { 0 };
    positiveNumberArray[20] = 1;
    bool negativeNumberArray[SIZE_OF_NUMBER] = { 0 };
    for (int i = 0; i < SIZE_OF_NUMBER; i++) {
        negativeNumberArray[i] = 1;
    }
    negativeNumberArray[21] = 0;
    return conversionToDecimal(positiveNumberArray) == 2048 && conversionToDecimal(negativeNumberArray) == -1025;
}

int main(void) {
    int firstNumber = -1;
    int secondNumber = -1;
    int decimalSumNumber = -1;
    bool binaryFirstNumber[SIZE_OF_NUMBER] = { 0 };
    bool binarySecondNumber[SIZE_OF_NUMBER] = { 0 };
    bool binarySumArray[SIZE_OF_NUMBER] = { 0 };

    bool errorCode = false;

    setlocale(LC_ALL, "Rus");

    if (!testComparingTwoArrays()) {
        printf("Тест areArraysEqual не пройден\n");
        return true;
    }

    if (!testGetBinaryNumber()) {
        printf("Тест getBinaryNumber не пройден\n");
        return true;
    }

    if (!testBinarySum()) {
        printf("Тест binarySum не пройден\n");
        return true;
    }

    if (!testConversionToDecimal()) {
        printf("Тест conversionToDecimal не пройден\n");
        return true;
    }

    readUserInput(&firstNumber, &secondNumber, &errorCode);
    if (errorCode) {
        return errorCode;
    }

    getBinaryNumber(firstNumber, binaryFirstNumber);
    getBinaryNumber(secondNumber, binarySecondNumber);
    binarySum(binaryFirstNumber, binarySecondNumber, binarySumArray);

    printf("Двоичное представление первого числа в дополнительном коде:\n");
    printBoolArray(binaryFirstNumber, SIZE_OF_NUMBER);
    printf("\nДвоичное представление второго числа в дополнительном коде:\n");
    printBoolArray(binarySecondNumber, SIZE_OF_NUMBER);
    printf("\nДвоичная сумма:\n");
    printBoolArray(binarySumArray, SIZE_OF_NUMBER);
    decimalSumNumber = conversionToDecimal(binarySumArray);
    printf("\nДесятичная сумма (в кольце вычетов по модулю 2 147 483 648):\n%d", decimalSumNumber);

    return errorCode;
}