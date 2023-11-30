# include <stdio.h>

int main(){
    char* line0 = "  *  \n";
    char* line1 = " ***\n";
    char* line2 = "*****\n";
    int i;
    for (i=0; i<3; i++) {
        if (i == 0){
            printf("%s", line0);
        }
        if (i == 1){
            printf("%s", line1);
        }
        if (i == 2){
            printf("%s", line2);
        }
    }
    return 0;
}