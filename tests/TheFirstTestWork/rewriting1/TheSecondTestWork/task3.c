#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int task3(bool *errorCode) {
    char ñharacter, previousÑharacter = '\0';

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Îøèáêà îòêğûòèÿ ôàéëà!\n");
        *errorCode = true;
        return;
    }

    printf("Èñõîäíûé òåêñò:\n");

    while (fscanf(file, "%c", &ñharacter) == 1) {
        printf("%c", ñharacter);
    }

    rewind(file);

    printf("\n\nÒåêñò ñ óäàëåíèåì ïîâòîğÿşùèõñÿ ñèìâîëîâ:\n");

    while (fscanf(file, "%c", &ñharacter) == 1) {
        if (ñharacter != previousÑharacter) {
            printf("%c", ñharacter);
            previousÑharacter = ñharacter;
        }
    }

    fclose(file);
}

