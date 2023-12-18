#include <stdio.h>
double variance(int len, int numbers[], double avg){
    double sum = 0.0;
    for (int i = 0; i < len; i++) {
        sum += (numbers[i] - avg) * (numbers[i] - avg);
    };
    return sum/len;
}

double average(int len, int numbers[]) {
    double sum = 0.0;
    for (int i = 0; i < len; i++) {
        sum += numbers[i];
    }
    double avg = sum/len;
    return avg;
}

void combine_avg(double* avg, double* vrz, int len, int numbers[]) {
    *avg = average(len,numbers);
    *vrz = variance(len, numbers, *avg);
}

int main() {
    printf("Wie viele Zahlen sollte das Array enthalten?\n");
    int n;
    scanf("%d", &n);
    int nums[n];
    // Jetzt das Array befüllen
    for (int i = 0; i < n; i++) {
        int x;
        printf("Bitte %d. Zahl eingeben:\n", i+1);
        scanf("%d", &x);
        nums[i] = x;
    }
    double avg, vrz;
    combine_avg(&avg, &vrz, n, nums);

    printf("Mittelwert: %.1f\n", avg);
    printf("Varianz: %.1f\n", vrz);
    return 0;
}