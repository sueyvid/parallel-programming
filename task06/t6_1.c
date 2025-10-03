// race_condition_without_synchronization.c
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 1000000

int main() {
    int count = 0;
    srand(time(NULL));
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        double x = rand() / (double)RAND_MAX;
        double y = rand() / (double)RAND_MAX;
        if (x * x + y * y <= 1) {
            count++;
        }
    }

    double pi = 4.0 * count / N;
    printf("Pi = %f\n", pi);

    return 0;
}