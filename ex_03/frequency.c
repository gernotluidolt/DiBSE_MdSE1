#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Überprüfung, ob mindestens ein Kommandozeilenparameter angegeben wurde
    if (argc < 2) {
        fprintf(stderr, "Fehler: Kein Kommandozeilenparameter angegeben.\n");
        return 1;
    }

    // Bestimmen der Gesamtlänge der Eingabe
    int totalLength = 1; // Beginne mit 1 für das terminierende Nullzeichen
    for (int i = 1; i < argc; i++) {
        totalLength += strlen(argv[i]) + 1; // +1 für das Leerzeichen
    }

    // Allokieren des Speichers für den zusammengefügten String
    char *concatenated = malloc(totalLength);
    if (concatenated == NULL) {
        fprintf(stderr, "Speicherzuweisung fehlgeschlagen\n");
        return 1;
    }

    concatenated[0] = '\0'; // Anfangen mit einem leeren String

    // Zusammenfügen der Strings
    for (int i = 1; i < argc; i++) {
        strcat(concatenated, argv[i]);
        if (i < argc - 1) {
            strcat(concatenated, " "); // Leerzeichen zwischen Argumenten hinzufügen
        }
    }

    // Array für die Häufigkeit jedes ASCII-Zeichens
    int frequency[256] = {0};
    char *str = concatenated; // Zeiger auf den zusammengefügten String

    // Zählen der Häufigkeit jedes Zeichens
    while (*str) {
        frequency[(unsigned char)(*str)]++;
        str++;
    }

    // Ausgabe der Häufigkeiten in sortierter Reihenfolge
    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            printf("Zeichen: '%c' - Häufigkeit: %d\n", i, frequency[i]);
        }
    }
    return 0;
}
