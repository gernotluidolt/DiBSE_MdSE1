# include <stdlib.h>
# include <stdio.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;

    if (num % 2 == 0 || num % 3 == 0) return 0;

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }

    return 1;
}


int main(int argc, char *args[]) {
    if (argc != 2) {
        printf("Bitte genau einen Kommandzeilenparameter angeben!");
        return 1;
    }
    int num = atoi(args[1]);
    if (num < 1) {
        printf("Bitte eine natürliche Zahl als Input!");
        return 2;
    }
    int colums = 10;
    int count  = 0;
    for (int i = 0; i < num; i++){

        if (is_prime(i)) {
            printf("%d\t", i);
            count++;
        }
        if (count == colums){
            printf("\n");
            count = 0;
        }
    }
    printf("\n");

    return 0;
}