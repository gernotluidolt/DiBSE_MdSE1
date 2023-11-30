# include <stdio.h>
# include <stdlib.h>

char* is_odd(int num) {
    if (num % 2 == 0) {
        return "false";
    } else {
        return "true";
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        char* result = is_odd(atoi(argv[1]));
        printf("%s\n", result);
        return 0;
    }
}