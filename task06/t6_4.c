// race_condition.c
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 1000000

int main() {
    int total_count = 0;
    int count = 0;
    srand(time(NULL));
    #pragma omp parallel default(none) firstprivate(count) shared(total_count)
    {
        #pragma omp for
        for (int i = 0; i < N; i++) {
            double x = rand() / (double)RAND_MAX;
            double y = rand() / (double)RAND_MAX;
            if (x * x + y * y <= 1) {
                count++;
            }
        }

        #pragma omp critical
        total_count += count;
    }

    double pi = 4.0 * total_count / N;
    printf("Pi = %f\n", pi);

    return 0;
}