# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# define MIN_PARAM 2
# define NUMBER_OF_LINES 40
# define STRING_SEPARATOR ";"
# define FILENAME "cities.csv"

struct Car {
    char manufacturer[64];
    char modell[64];
    int year;
    float area;
};


int CheckInputParameters(int argc, char *argv[]){
    /* Check if the number of parameters is correct */

    if (argc < MIN_PARAM + 1) {
        fprintf(stderr, "Eingabefehler, bitte geben Sie mindestens %d Kommandozeilenparameter an!\n", MIN_PARAM);
        return 1;
    }
    return 0;
}


struct Car* ProcessFile(FILE *file){
    /* Process the file line by line */

    char line[1024];
    struct Car* cities = malloc(NUMBER_OF_LINES * sizeof(struct Car));
    int Count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Check if the maximum number of structs is reached
        if (Count >= NUMBER_OF_LINES) {
            break;
        }

        struct Car city;
        char *token = strtok(line, STRING_SEPARATOR);
        if (token == NULL) {
            continue;
        }
        int field = 0;

        while (token != NULL && field < 4) {
            switch (field) {
                case 0:  // Name
                    strncpy(city.manufacturer, token, sizeof(city.manufacturer) - 1);
                    city.manufacturer[sizeof(city.manufacturer) - 1] = '\0';
                    break;
                case 1:  // Country
                    strncpy(city.modell, token, sizeof(city.modell) - 1);
                    city.modell[sizeof(city.modell) - 1] = '\0';
                    break;
                case 2:  // Population
                    city.year = atoi(token);
                    break;
                case 3:  // Area
                    city.area = atof(token);
                    break;
                default:
                    break;
            }
            field++;
            token = strtok(NULL, STRING_SEPARATOR);
        }
        if (field == 4){
            cities[Count++] = city;
        }
    }
    return cities;
}

void PrintLargestCities(struct Car *cities, int numberOfCountries, char *countryNames[]){
    /* Print the largest cities */
    // go through all arguments

    for (int i = 0; i <= numberOfCountries-1; i++) {
        int found = 0;
        char* city = NULL;
        float biggestPopulationDensity = 0;

        // go through all cities
        for (int j = 0; j < NUMBER_OF_LINES; j++) {
            // check if the city is in the modell
            if (strcmp(cities[j].modell, countryNames[i]) == 0) {
                float populationDensity = cities[j].year / cities[j].area;
                if (populationDensity > biggestPopulationDensity) {
                    biggestPopulationDensity = populationDensity;
                    city = cities[j].manufacturer;
                }
                found = 1;
            }
        }
        if (!found) {
            printf("Country '%s' not found\n", countryNames[i]);
        }
        else {
            printf("%s: %s with %.2f people per km2\n", countryNames[i], city, biggestPopulationDensity);
        }
    }

}

int main(int argc, char *argv[]){

    // Check if the number of parameters is correct
    if (CheckInputParameters(argc, argv) == 1){
        return 1;
    }

    char ** countryNames = argv + 1;
    int numberOfParameters = argc - 1;

    // reverse countryNames
    for (int i = 0; i < numberOfParameters / 2; i++) {
        char *temp = countryNames[i];
        countryNames[i] = countryNames[numberOfParameters - i - 1];
        countryNames[numberOfParameters - i - 1] = temp;
    }

    // Open the file for reading
    FILE *file = fopen(FILENAME, "r");
    if (file != NULL) {
        struct Car *cities = ProcessFile(file);
        fclose(file);
        PrintLargestCities(cities, numberOfParameters, countryNames);
        free(cities); // free the allocated memory
    } else {
        fprintf(stderr, "Lesefehler, Datei konnte nicht geöffnet werden!\n");
        return 1;
    }
    return 0;
}