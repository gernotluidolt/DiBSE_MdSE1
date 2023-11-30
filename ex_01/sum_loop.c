#include <stdio.h>

int sum_loop() {
    int num;
    int sum = 0;
    for (num = 2; num < 1000; num += 8) {
        sum += num;
    }
    return sum;
}

int main() {
    int result = sum_loop();
    printf("%d\n", result);
    return 0;
}