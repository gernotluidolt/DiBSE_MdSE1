#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 20
#define MAX_HOBBIES 5
#define BUFFER_SIZE 1024

typedef struct {
    char first_name[50];
    char last_name[50];
    int age;
    char hobbies[MAX_HOBBIES][50];
} Person;

int main() {
    FILE *file;
    char buffer[BUFFER_SIZE];
    Person persons[MAX_LINES];
    int person_count = 0;

    file = fopen("persons_input.txt", "r");
    if (!file) {
        perror("Fehler beim Öffnen der Datei");
        return 1;
    }

    while (fgets(buffer, BUFFER_SIZE, file) && person_count < MAX_LINES) {
        char *token;
        token = strtok(buffer, ";");
        if (token) {
            strcpy(persons[person_count].first_name, token);
            token = strtok(NULL, ";");
        }
        if (token) {
            strcpy(persons[person_count].last_name, token);
            token = strtok(NULL, ";");
        }
        if (token) {
            persons[person_count].age = atoi(token);
            token = strtok(NULL, ";");
        }
        if (token) {
            char *hobby;
            int hobby_count = 0;
            hobby = strtok(token, ",");
            while (hobby && hobby_count < MAX_HOBBIES) {
                strcpy(persons[person_count].hobbies[hobby_count], hobby);
                hobby = strtok(NULL, ",");
                hobby_count++;
            }
        }

        person_count++;
    }

    fclose(file);

    // Durchsuchen der Personen und Ausgabe der Nachnamen
    for (int i = 0; i < person_count; i++) {
        int hasDancing = 0;
        for (int j = 0; j < MAX_HOBBIES; j++) {
            if (strcmp(persons[i].hobbies[j], "Tanzen") == 0) {
                hasDancing = 1;
                break;
            }
        }
        if (persons[i].age >= 20 && persons[i].age <= 30 && hasDancing) {
            printf("%s\n", persons[i].last_name);
        }
    }

    return 0;
}
