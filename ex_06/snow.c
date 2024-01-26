#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_DAYS 8

int main() {
    char ort[MAX_LINE_LENGTH];
    int tag;

    printf("Geben Sie einen Ort an:\n");
    scanf("%s", ort);

    printf("Geben Sie einen Tag an:\n");
    scanf("%d", &tag);

    if (tag < 1 || tag > MAX_DAYS) {
        fprintf(stderr, "Eingabefehler, bitte geben Sie einen Tag zwischen 1 und 8 an!\n");
        return 1;
    }

    int summe = 0;
    char filename[MAX_LINE_LENGTH];
    sprintf(filename, "snow_data/%s_%d.txt", ort, tag);

    FILE *output = fopen(filename, "w");
    if (output == NULL) {
        fprintf(stderr, "Schreibfehler, Datei konnte nicht geöffnet werden!\n");
        return 1;
    }

    for (int i = 1; i <= tag; i++) {
        sprintf(filename, "snow_data/%d.txt", i);
        FILE *input = fopen(filename, "r");
        if (input == NULL) {
            fprintf(stderr, "Lesefehler, Datei konnte nicht geöffnet werden!\n");
            fclose(output);
            return 1;
        }

        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), input) != NULL) {
            char *token = strtok(line, ";");
            if (strcmp(token, ort) == 0) {
                token = strtok(NULL, ";");
                int schneefall = atoi(token);
                summe += schneefall;
                fprintf(output, "Tag %d: %d\n", i, schneefall);
                break;
            }
        }

        fclose(input);
    }

    fprintf(output, "Summe: %d\n", summe);
    fclose(output);

    printf("Die Ergebnisse Ihrer Anfrage wurden erfolgreich in eine Datei geschrieben.\n");

    return 0;
}