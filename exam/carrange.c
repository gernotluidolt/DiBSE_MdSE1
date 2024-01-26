# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define PARAM 2 // Anzahl der gewünschten Kommandozeilenparameter
# define FILENAME "cars.csv" // Name der Datei
# define MAXCOUNT 40 // max. Zeilen die berücksichtigt werden

/*
 * Es funktioniert:
 * - Check ob mehr oder weniger als 2 Kommandozeilenparameter
 * - Check ob der erste Parameter eine Zahl ist
 * - Die gewünschten Fehlermeldungen
 * - Verhalten bei mehr oder weniger als 40 Zeilen
 * - Es sollte also alles nach Angabe passen
 */

// defines car struct
typedef struct {
    char brand[64];
    char model[64];
    float fuel;
    int tank;
    char colors[3][64];
    float range;
} Car;

// define an array of Car
Car cars[MAXCOUNT];


int main(int argc, char *argv[]){
    // Check if the number of parameters is correct
    if (argc != PARAM + 1) {
        fprintf(stderr, "Eingabefehler, bitte geben Sie %d Kommandozeilenparameter an!\n", PARAM);
        exit(1);
    }

    // Check if the first parameter is a number
    char* strend;
    int minRange = strtol(argv[1], &strend, 10);
    if (strend == argv[1] || *strend != '\0') {
        fprintf(stderr, "Eingabefehler, bitte geben Sie eine Zahl als ersten Parameter an!\n");
        exit(1);
    } else if (minRange < 0) {
        fprintf(stderr, "Eingabefehler, bitte geben Sie eine positive Zahl als ersten Parameter an!\n");
        exit(1);
    }


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
        memset(&cars[count], 0, sizeof(Car));

        int retval = sscanf(buffer, "%63[^:]:%63[^:]:%f:%d:%63[^,\n],%63[^,\n],%63[^,\n]",
                            cars[count].brand,
                            cars[count].model,
                            &cars[count].fuel,
                            &cars[count].tank,
                            cars[count].colors[0], cars[count].colors[1], cars[count].colors[2]);
        // Prüfen, ob das Element richtig gelesen wurden
        if (retval == 7) {
            cars[count].range = (cars[count].tank / cars[count].fuel) * 100;
            count++;
        } else {
            printf("retval: %d\n", retval);
            fprintf(stderr, "Fehler beim Lesen der Zeile %d\n", count + 1);
        }
        // Wenn die maximale Anzahl an structs erreicht ist, dann abbrechen
        if (count >= MAXCOUNT) {
            break;
        }
    }
    fclose(file);

    /* Testausgabe
    for (int i = 0; i < count; ++i) {
        printf("%s %s %f %d %s %s %s %f\n", cars[i].brand, cars[i].model, cars[i].fuel, cars[i].tank, cars[i].colors[0], cars[i].colors[1], cars[i].colors[2], cars[i].range);
    }
     */

    // reverse array (Hätte auch im for loop unten mit runterzählen statt rauf passieren können)
    for (int i = 0; i < count / 2; i++) {
        Car tmp = cars[i];
        cars[i] = cars[count - i - 1];
        cars[count - i - 1] = tmp;
    }

    // Zählt wie viele passende Autos gefunden wurden
    int carCount = 0;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 3; j++) {
            if (strcmp(cars[i].colors[j], argv[2]) == 0 && cars[i].range >= minRange) {
                printf("%s %s: %.2f km\n", cars[i].brand, cars[i].model, cars[i].range);
                carCount++;
            }
        }
    }
    // Kein passendes Auto gefunden
    if (carCount == 0) {
        fprintf(stderr, "Parameterfehler. Keine Autos gefunden!\n");
        exit(1);
    }
}