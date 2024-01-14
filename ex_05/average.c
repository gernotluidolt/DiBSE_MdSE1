#include <stdio.h>
#include <stdlib.h>

// Funktion zum Berechnen des Durchschnitts
double calculate_average(int *arr, int n) {
    if (n == 0) return 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (double)sum / n;
}

int main() {
    int block_size = 5;
    int size = block_size;
    int count = 0;
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Speicherallokation fehlgeschlagen\n");
        return 1;
    }

    printf("Geben Sie die Elemente Ihres Arrays an:\n");

    while (1) {
        printf("Element #%d:\n", count + 1);

        char input[50];
        if (!fgets(input, 50, stdin)) {
            fprintf(stderr, "Fehler beim Einlesen\n");
            free(arr);
            return 1;
        }

        if (input[0] == '\n') {
            break;
        }

        int num;
        if (sscanf(input, "%d", &num) == 1) {
            arr[count++] = num;
            if (count == size) {
                size += block_size;
                int *temp = realloc(arr, size * sizeof(int));
                if (temp == NULL) {
                    fprintf(stderr, "Speichererweiterung fehlgeschlagen\n");
                    free(arr);
                    return 1;
                }
                arr = temp;
            }
        }
    }

    double average = calculate_average(arr, count);
    printf("Eingabe beendet.\n");
    printf("Der Durchschnitt Ihres Arrays ist: %.1f\n", average);

    free(arr);
    return 0;
}
