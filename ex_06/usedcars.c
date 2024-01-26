# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAXCOUNT 42
# define FILENAME "gebrauchtwagen.csv"

typedef struct {
    char brand[64];
    char model[64];
    int year;
    int km;
    float price;
    float pricePerKm;
    char extras[6][64];
} Car;

// define an array of cars
Car cars[MAXCOUNT];

int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Eingabefehler, bitte geben Sie mindestens 2 Kommandozeilenparameter an!\n");
        exit(1);
    }

    // Check if the first parameter is a number
    char* strend;
    int minYear = strtol(argv[1], &strend, 10);
    if (strend == argv[1] || *strend != '\0') {
        fprintf(stderr, "Eingabefehler, bitte geben Sie eine Zahl als ersten Parameter an!\n");
        exit(1);
    } else if (minYear < 0) {
        fprintf(stderr, "Eingabefehler, bitte geben Sie eine positive Zahl als ersten Parameter an!\n");
        exit(1);
    }

    float maxpricePerKm = strtof(argv[2], &strend);
    if (strend == argv[2] || *strend != '\0') {
        fprintf(stderr, "Eingabefehler, bitte geben Sie eine Zahl als zweiten Parameter an!\n");
        exit(1);
    } else if (maxpricePerKm <= 0.0) {
        fprintf(stderr, "Eingabefehler, bitte geben Sie eine positive Zahl als zweiten Parameter an!\n");
        exit(1);
    }

    // read the file
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Lesefehler, Datei konnte nicht geöffnet werden!\n");
        exit(1);
    }

    int count = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        memset(&cars[count], 0, sizeof(Car));
        // returnwert eines scanf ist die Anzahl der gelesenen elemente
        int retval = sscanf(buffer, "%63[^:]:%63[^:]:%d:%d:%f:%63[^#\n]#%63[^#\n]#%63[^#\n]#%63[^#\n]#%63[^#\n]#%63[^#\n]",
               cars[count].brand,
               cars[count].model,
               &cars[count].year,
               &cars[count].km,
               &cars[count].price,
               cars[count].extras[0], cars[count].extras[1], cars[count].extras[2],
               cars[count].extras[3], cars[count].extras[4], cars[count].extras[5]);
        // Prüfen, ob das Element richtig gelesen wurden
        if (retval >= 5 && retval <= 11) {
            cars[count].pricePerKm = cars[count].price / cars[count].km;
            count++;
        } else {
            fprintf(stderr, "Fehler beim Lesen der Zeile %d\n", count + 1);
        }
        // Wenn die maximale Anzahl an Autos erreicht ist, dann abbrechen
        if (count >= MAXCOUNT) {
            break;
        }
    }
    fclose(file);

    for (int i = count; i >= 0; i--) {
        if (cars[i].year >= minYear && cars[i].pricePerKm <= maxpricePerKm) {
            int match = 0;
            for (int j = 3; j < argc; j++) {
                for (int k = 0; k < 6; k++) {
                    if (strcmp(argv[j], cars[i].extras[k]) == 0) {
                       match++;
                       break;
                    }
                }
            }
            if (match == argc - 3) {
                printf("%s %s, Baujahr %d, Kilometerstand: %d km, Preis: %.2f Euro\n\t Zusatzausstattung: %s %s %s %s %s %s\n",
                       cars[i].brand, cars[i].model, cars[i].year, cars[i].km, cars[i].price,
                       cars[i].extras[0], cars[i].extras[1], cars[i].extras[2],
                       cars[i].extras[3], cars[i].extras[4], cars[i].extras[5]);
            }
        }
    }
}