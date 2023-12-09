# include <stdio.h>
# include <stdlib.h>

int main(int argc, char *args[]){
    if (argc != 2)
    {
        printf("Bitte genau einen Kommandzeilenparameter angeben!");
        return 1;
    }
        int num = atoi(args[1]);
        if (num < 1)
        {
            printf("Bitte eine natürliche Zahl als Input!");
            return 2;
        }
        int stars = 1;
        int space = num - 1;
        for (int i = 0; i < num; i++) {
        for (int j = 0; j < space; j++){
        printf(" ");
        }
        for (int k = 0; k < stars; k++){
        printf("*");
        }
        printf("\n");
        space -= 1;
        stars += 2;
    }
    return 0;
}