#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

long convert_to_number(const char *str) {
    char *endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);

    if (errno != 0 || *endptr != '\0' || str == endptr) {
        // Conversion error or non-numeric characters found
        return -1;
    }

    return val;
}

int main() {
    char input[100];
    long num1, num2;
    char op;
    double result;

    while (1) {
        printf("> Geben Sie Zahl 1 ein:\n");
        if (scanf("%99s", input) != 1) {
            fprintf(stderr, "Fehler beim Lesen der Eingabe.\n");
            continue;
        }
        if (strcmp(input, "exit") == 0) {
            printf("> Rechner wird geschlossen\n");
            break;
        }

        num1 = convert_to_number(input);
        if (num1 == -1) {
            fprintf(stderr, "Falsche Eingabe! Keine gültige Zahl.\n");
            continue;
        }

        printf("> Geben Sie die Operation ein:\n");
        scanf("%99s", input);
        if (strcmp(input, "exit") == 0) {
            printf("> Rechner wird geschlossen\n");
            break;
        }
        op = input[0];

        if (op != '+' && op != '-' && op != '*' && op != '/') {
            fprintf(stderr, "Falsche Eingabe!\n");
            continue;
        }

        printf("> Geben Sie Zahl 2 ein:\n");
        scanf("%99s", input);
        if (strcmp(input, "exit") == 0) {
            printf("> Rechner wird geschlossen\n");
            break;
        }

        num2 = convert_to_number(input);
        if (num2 == -1) {
            fprintf(stderr, "Falsche Eingabe! Keine gültige Zahl.\n");
            continue;
        }

        switch(op) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                if (num2 == 0) {
                    fprintf(stderr, "Falsche Eingabe!\n");
                    continue;
                }
                result = (double)num1 / num2;
                break;
        }

        printf("> Ergebnis: %.2f\n", result);
    }

    return 0;
}
