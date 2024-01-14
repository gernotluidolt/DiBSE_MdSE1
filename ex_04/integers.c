#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file;
    char line[1024];

    // Open the file for writing
    file = fopen("integers_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    printf("Geben Sie Ihren Text ein:\n");
    while (1) {
        // Read a line from the standard input
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        // Check for empty line to end input
        if (strcmp(line, "\n") == 0) {
            break;
        }

        int length = strlen(line);
        int number_found = 0;
        int number_written = 0;

        for (int i = 0; i < length; i++) {
            // Manually check if the character is a digit
            if (line[i] >= '0' && line[i] <= '9') {
                fputc(line[i], file);
                number_found = 1;
                number_written = 1;
            } else if (number_found) {
                // If the previous character was a digit, print a space
                fputc(' ', file);
                number_found = 0;
            }
        }

        // Print a newline character only if a number was written in this line
        if (number_written) {
            fputc('\n', file);
        }
    }

    fclose(file);
    return 0;
}
