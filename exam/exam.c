# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MIN_PARAM 2
# define FILENAME "filename.csv"
# define MAXCOUNT 42

typedef struct {
    int member;
} Test;

// define an array of struct
Test tests[MAXCOUNT];


int main(int argc, char *argv[]){
    // Check if the number of parameters is correct
    if (argc < MIN_PARAM + 1) {
        fprintf(stderr, "Eingabefehler, bitte geben Sie mindestens %d Kommandozeilenparameter an!\n", MIN_PARAM);
        exit(1);
    } else {
        printf("Has worked\n");
    }

    // check if input parameters are valid


    // open the file
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Lesefehler, Datei konnte nicht geöffnet werden!\n");
        exit(1);
    }

    int count = 0;
    char buffer[1024];

    // befüllen des struct array
    while (fgets(buffer, sizeof(buffer), file)) {
        memset(&tests[count], 0, sizeof(tests));
        // returnwert eines scanf ist die Anzahl der gelesenen elemente
        // Beispiel string zum Einlesen "63[^:]:%63[^:]:%d:%d:%f"  WICHTIG: ZUM SCHLUSS WENN STRING newline auslassen 63[^#\n]
        int retval = sscanf(buffer, "%d",
                            &tests[count].member);
        // Prüfen, ob das Element richtig gelesen wurden
        if (retval == 1) {
            // wenn ein Wert zu errechnen ist, dann hier
            // test[count].pricePerKm = test[count].price / test[count].km;
            count++;
        } else {
            fprintf(stderr, "Fehler beim Lesen der Zeile %d\n", count + 1);
        }
        // Wenn die maximale Anzahl an structs erreicht ist, dann abbrechen
        if (count >= MAXCOUNT) {
            break;
        }
    }
    fclose(file);

    // logik für die Aufgabe ZUERST TESTEN OB DIE STRUCTS RICHTIG BEFÜLLT WURDEN


}

