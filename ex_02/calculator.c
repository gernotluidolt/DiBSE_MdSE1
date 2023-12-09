#include "operations.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *args[]){
    if (argc != 4)
    {
        printf("Bitte genau drei Kommandzeilenparameter angeben!");
        return 1;
    }
    int x = atoi(args[1]);
    int y = atoi(args[3]);

    char* operation = args[2];

    int result;

    if (strcmp(operation, "+") == 0) {
        result = add(x,y);
    } else if (strcmp(operation, "-") == 0) {
        result = subtract(x,y);
    } else if (strcmp(operation, "*") == 0) {
        result = multiply(x,y);
    } else if (strcmp(operation, "/") == 0) {
        result = divide(x,y);
    } else {
        printf("Operator not valid, please use +, -, \"*\", or /");
        return 1;
    }
    printf("%d\n", result);
    return 0;
}