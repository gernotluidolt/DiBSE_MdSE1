# import <stdio.h>
# import <string.h>
# import <stdlib.h>

int main() {
    printf("Geben Sie einen Ort an: ");
    fflush(stdout);

    char ort[64];
    fgets(ort, 64, stdin);

    // remove the newline character
    if (ort[strlen(ort) - 1] != '\0'){
        ort[strlen(ort) - 1] = '\0';
    }


    printf("Geben Sie einen Tag an: ");
    fflush(stdout);

    char tmp[32];
    fgets(tmp, 32, stdin);
    // check if input is int and save to tmp
    char* strend;
    int tag = strtol(tmp, &strend, 10);
    if (strend == tmp || *strend != '\n') {
        fprintf(stderr, "Eingabefehler, bitte geben Sie eine Zahl an!\n");
        exit(1);
    } else if (tag < 1 || tag > 8) {
        fprintf(stderr, "Eingabefehler, bitte geben Sie einen Tag von 1 bis 8 an!\n");
        exit(1);
    }

    int snowsum = 0;
    FILE* outfile = NULL;
    for (int i = 1; i <= tag; i++){
        char filename[128];
        sprintf(filename, "snow_data/%d.txt", i);
        FILE* file = fopen(filename, "r");
        if (file == NULL){
            fprintf(stderr, "Lesefehler, Datei konnte nicht geöffnet werden!\n");
            exit(1);
        }

        char buffer[128];
        while (fgets(buffer, 128, file)){
            char ortf[64];
            int snow;
            sscanf(buffer, "%64[^;];%d", ortf, &snow);
            if (strcmp(ort, ortf) == 0) {
                if (outfile == NULL)
                {
                    char outfilename[64];
                    snprintf(outfilename, sizeof(outfilename), "snow_data/%s_%d.txt", ort, tag);
                    outfile = fopen(outfilename, "w");
                    if (outfile == NULL) {
                        perror("Could not create file");
                        exit(1);
                    }
                }
                fprintf(outfile, "Tag %d: %d\n", i, snow);
                snowsum += snow;
                break;
            }
        }
        fclose(file);
    }
    if (outfile) {
        fprintf(outfile, "Summe: %d\n", snowsum);
        printf("Datei wurde erfolgreich erstellt");
    }
    else {
        printf("Datei konnte nicht erzeugt werden!");
    }

}