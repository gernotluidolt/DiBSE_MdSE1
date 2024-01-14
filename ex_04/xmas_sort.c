#include "xmas_sort.h"

void xmas_sort(int* array, const int n) {
    if (n < 2) {
        // Für Arrays der Länge 0 oder 1 ist nichts zu tun.
        return;
    }

    int i = 0;
    while (i < n - 1) {
        if (array[i] > array[i + 1]) {
            // Vertausche die Elemente.
            int temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;

            // Gehe einen Schritt zurück, wenn möglich.
            if (i > 0) {
                i--;
            }
        } else {
            // Gehe einen Schritt nach rechts.
            i++;
        }
    }
}
