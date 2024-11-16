#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "../Tree/tree.h"

void printTheBackgroundInformation() {
    printf(
        "0 – Выход\n"
        "1 – Добавить значение в словарь\n"
        "2 – Вывести значение по ключу\n"
        "3 – Проверить наличие заданного ключа в словаре\n"
        "4 – Проверить наличие заданного ключа в словаре\n"
        "5 - Удалить заданный ключ и связанное с ним значение из словаря\n\n"
    );
}

void callTheFunction(int functionCode, bool* errorCode) {
    while (functionCode != 0) {
        if (functionCode == 1) {
            printf("Не готово\n");
        }
        if (functionCode == 2) {
            printf("Не готово\n");
        }
        if (functionCode == 3) {
            printf("Не готово\n");
        }
        functionCode = getTheFunctionCodeFromTheUser();
    }
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getTheFunctionCodeFromTheUser(void) {
    int functionCode = -1;
    printTheBackgroundInformation();
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 5 || functionCode < 0 || scanfReturns != 1) {
        printf("Введён некорректный номер команды, попробуйте ещё раз:\n");
        printTheBackgroundInformation();
        clearBuffer();
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;

    runTheTreeTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    callTheFunction(getTheFunctionCodeFromTheUser(), &errorCode);
    return errorCode;
}