# include <stdio.h>
# include <string.h>
# include <stdlib.h>

// check if command line input is int

printf("Geben Sie eine Zahl: ");
fflush(stdout);

char tmp[32];
fgets(tmp, 32, stdin);
char* strend;
int num = strtol(tmp, &strend, 10);
if (strend == tmp || *strend != '\n') {
    fprintf(stderr, "Eingabefehler, bitte geben Sie eine Zahl an!\n");
    exit(1);
} else if (num < 1 || num > 8) {
    fprintf(stderr, "Eingabefehler, bitte geben Sie eine Zahl von 1 bis 8 an!\n");
    exit(1);
}

// Check if input parameter is number
char* strend;
int num = strtol(argv[1], &strend, 10);
if (strend == argv[1] || *strend != '\0') {
    fprintf(stderr, "Eingabefehler, bitte geben Sie eine Zahl als ersten Parameter an!\n");
    exit(1);
} else if (minYear < 0) {
    fprintf(stderr, "Eingabefehler, bitte geben Sie eine positive Zahl als ersten Parameter an!\n");
    exit(1);
}


// check if command line input is float

printf("Geben Sie eine Zahl: ");
fflush(stdout);

char tmp[32];
fgets(tmp, 32, stdin);
char* strend;
float num = strtof(tmp, &strend);
if (strend == tmp || *strend != '\n') {
    fprintf(stderr, "Eingabefehler, bitte geben Sie eine Zahl an!\n");
    exit(1);
} else if (num < 1 || num > 8) {
    fprintf(stderr, "Eingabefehler, bitte geben Sie eine Zahl von 1 bis 8 an!\n");
    exit(1);
}


// compare strings

if (strcmp(str1, str2) == 0) {
    // match
}

// set string to new value
strcpy(strvar, "new value");

// replace newline character with null character
if (str[strlen(str) - 1] != '\0'){
    str[strlen(str) - 1] = '\0';
}

// Fehler ausgeben und Programm beenden
perror("Gewünschter Text");
exit(1);