#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#define _CRT_SECURE_NO_WARNINGS

#include "task3.h"
#include "task2.h"

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    bool* errorCode = false;

    printf("Задание 2:\n");
    task2(&errorCode);
    printf("Задание 3:\n");
    task3(&errorCode);
    return errorCode;
}