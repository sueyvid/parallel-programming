#include <stdlib.h> // Para srand() e rand()
#include <stdio.h>  // Para printf()
#include <time.h>   // Para time()

int main() {
    // Define a semente para srand() usando a hora atual do sistema
    srand(time(NULL));

    // Gera um número pseudoaleatório
    float numero = ((float) rand() / RAND_MAX) * 2.0f;

    printf("Número aleatório: %f\n", numero);

    return 0;
}
