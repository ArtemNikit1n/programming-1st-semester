#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int task3(bool *errorCode) {
    char �haracter, previous�haracter = '\0';

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("������ �������� �����!\n");
        *errorCode = true;
        return;
    }

    printf("�������� �����:\n");

    while (fscanf(file, "%c", &�haracter) == 1) {
        printf("%c", �haracter);
    }

    rewind(file);

    printf("\n\n����� � ��������� ������������� ��������:\n");

    while (fscanf(file, "%c", &�haracter) == 1) {
        if (�haracter != previous�haracter) {
            printf("%c", �haracter);
            previous�haracter = �haracter;
        }
    }

    fclose(file);
}

