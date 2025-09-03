// threads.c
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int main() {
    int value = omp_get_max_threads();
    printf("Threads máximo: %d\n", value);
    return 0;
}