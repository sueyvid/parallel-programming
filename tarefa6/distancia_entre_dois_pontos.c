#include <stdlib.h> // Para srand() e rand()
#include <stdio.h>  // Para printf()
#include <time.h>   // Para time()
#include <math.h>

int main() {
    float x = 2; float y = 1;
    int x_ = 1; int y_ = 1;

    double resultado;
    float x2; float y2;

    x2 = (x - x_) * (x - x_);
    y2 = (y - y_) * (y - y_);

    resultado = sqrt(x2 + y2);

    printf("Resultado: %f\n", resultado);

    return 0;
}
