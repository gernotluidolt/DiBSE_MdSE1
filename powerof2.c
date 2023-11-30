# include <stdio.h>
# include <stdlib.h>

int main(int argc, char *args[]){
    if (argc == 2){
        int i;
        int num = atoi(args[1]);
        int count = 0;
        for (i = 1; i<=num; i*=2){
            if (i == num){
                printf("%d\n", count);
            }
            count++;
        }
    }
}