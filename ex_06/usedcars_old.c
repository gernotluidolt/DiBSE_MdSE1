# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# define MIN_PARAM 2
# define NUMBER_OF_LINES 42
# define STRING_SEPARATOR ":"

int numberOfMembers = 6;

struct Features {
    char feature1[64];
    char feature2[64];
    char feature3[64];
    char feature4[64];
    char feature5[64];
    char feature6[64];
    };

struct Car {
    char manufacturer[64];
    char modell[64];
    int year;
    int km;
    float price;
    struct Features features;
};

float GetPricePerKm(struct Car car){
    return car.price / car.km;
}

int CheckInputParameters(int argc, char *argv[]){
    /* Check if the number of parameters is correct */

    if (argc < MIN_PARAM + 1) {
        fprintf(stderr, "Eingabefehler, bitte geben Sie mindestens %d Kommandozeilenparameter an!\n", MIN_PARAM);
        return 1;
    }
    return 0;
}

char** GetFeatures(char *text){
    char *token = strtok(text, "#");
    char **features = malloc(numberOfMembers * sizeof(char *));
    for (int i = 0; i < numberOfMembers; i++) {
        features[i] = "";
    }
    int count = 0;
    while (token != NULL && count < numberOfMembers) {
        features[count++] = strdup(token);
        token = strtok(NULL, "#");
    }
    return features;
}

struct Car* ProcessFile(FILE *file){
    /* Process the file line by line */

    char line[1024];
    struct Car* UsedCars = malloc(NUMBER_OF_LINES * sizeof(struct Car));
    int Count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Check if the maximum number of structs is reached
        if (Count >= NUMBER_OF_LINES) {
            break;
        }

        struct Car car;
        char *token = strtok(line, STRING_SEPARATOR);
        if (token == NULL) {
            continue;
        }
        int field = 0;
        char **features;
        while (token != NULL && field < numberOfMembers) {
            switch (field) {
                case 0:
                    strncpy(car.manufacturer, token, sizeof(car.manufacturer) - 1);
                    car.manufacturer[sizeof(car.manufacturer) - 1] = '\0';
                    break;
                case 1:
                    strncpy(car.modell, token, sizeof(car.modell) - 1);
                    car.modell[sizeof(car.modell) - 1] = '\0';
                    break;
                case 2:
                    car.year = atoi(token);
                    break;
                case 3:
                    car.km = atoi(token);
                    break;
                case 4:
                    car.price = atof(token);
                    break;
                case 5:
                    features = GetFeatures(token);
                    strcpy(car.features.feature1, features[0]);
                    strcpy(car.features.feature2, features[1]);
                    strcpy(car.features.feature3, features[2]);
                    strcpy(car.features.feature4, features[3]);
                    strcpy(car.features.feature5, features[4]);
                    strcpy(car.features.feature6, features[5]);
                    break;
                default:
                    break;
            }
            field++;
            token = strtok(NULL, STRING_SEPARATOR);
        }
        if (field == numberOfMembers){
            UsedCars[Count++] = car;
        }
    }
    return UsedCars;
}

int HasFeatures(char** wantedFeatures, struct Features features, int numberOfWantedFeatures){
    int HasFeatures;
    // check each wanted feature if it is in the features of the car
    for (int i = 0; i < numberOfWantedFeatures; i++){
        if (strcmp(wantedFeatures[i], features.feature1) == 0 || strcmp(wantedFeatures[i], features.feature2) == 0 || strcmp(wantedFeatures[i], features.feature3) == 0 || strcmp(wantedFeatures[i], features.feature4) == 0 || strcmp(wantedFeatures[i], features.feature5) == 0 || strcmp(wantedFeatures[i], features.feature6) == 0){
            HasFeatures = 0;
        } else {
            HasFeatures = 1;
            break;
        }
    }
    return HasFeatures;
}

void PrintCars(struct Car *cars, int minYear, float maxPricePerKm, char** wantedFeatures, int numberOfWantedFeatures){

    for (int i = 0; i < NUMBER_OF_LINES; i++){
        float tmpPricePerKm = GetPricePerKm(cars[i]);
        if (tmpPricePerKm <= maxPricePerKm && cars[i].year >= minYear){
            if (numberOfWantedFeatures > 0){
                if (HasFeatures(wantedFeatures, cars[i].features, numberOfWantedFeatures)){
                    printf("%s %s, Baujahr %d, Kilometerstand %d, Preis: %f Euro, Zusatzausstattung: %s %s %s %s %s %s\n", cars[i].manufacturer, cars[i].modell, cars[i].year, cars[i].km, cars[i].price, cars[i].features.feature1, cars[i].features.feature2, cars[i].features.feature3, cars[i].features.feature4, cars[i].features.feature5, cars[i].features.feature6);
                }
                continue;
            }
            printf("%s %s, Baujahr %d, Kilometerstand %d, Preis: %f Euro, Zusatzausstattung: %s %s %s %s %s %s\n", cars[i].manufacturer, cars[i].modell, cars[i].year, cars[i].km, cars[i].price, cars[i].features.feature1, cars[i].features.feature2, cars[i].features.feature3, cars[i].features.feature4, cars[i].features.feature5, cars[i].features.feature6);
        }
    }
}

int main(int argc, char *argv[]){
    // Check if the number of parameters is correct
    if (CheckInputParameters(argc, argv) == 1){
        return 1;
    }
    char** wantedFeatures = malloc((argc - 3) * sizeof(char*));
    int numberOfWantedFeatures = 0;
    if (argc > 3){
        numberOfWantedFeatures = argc - 3;
        for (int i = 3; i < argc; i++){
            wantedFeatures[i-3] = strdup(argv[i]);
        }
    }

    // Open the file for reading
    FILE *file = fopen("gebrauchtwagen.csv", "r");
    if (file != NULL) {
        struct Car *cars = ProcessFile(file);
        fclose(file);

        // reverse the array
        for (int i = 0; i < NUMBER_OF_LINES / 2; i++) {
            struct Car temp = cars[i];
            cars[i] = cars[NUMBER_OF_LINES - i - 1];
            cars[NUMBER_OF_LINES - i - 1] = temp;
        }

        int minYear = atoi(argv[1]);
        float maxPricePerKm = atof(argv[2]);
        PrintCars(cars, minYear, maxPricePerKm, wantedFeatures, numberOfWantedFeatures);
        free(cars); // free the allocated memory
        free(wantedFeatures);
    } else {
        fprintf(stderr, "Lesefehler, Datei konnte nicht geöffnet werden!\n");
        return 1;
    }
    return 0;
}