// aproximacao_de_pi.c
#include <stdio.h>
#include <math.h>

#define PI_REAL 3.14159265358979323846

int main() {
    int i, termos;
    double pi = 0.0;

    termos = 1000000000;

    for (i = 0; i < termos; i++) {
        if (i % 2 == 0) {
            pi += 1.0 / (2 * i + 1);
        } else {
            pi -= 1.0 / (2 * i + 1);
        }
    }

    pi *= 4.0;

    printf("Aproximação de Pi com %d termos: %.15f\n", termos, pi);

    double acuracia = PI_REAL - pi;
    printf("Acurácia: %.15f\n", acuracia);

    // char real[] = "3.14159265358979323846";
    // char calculado[18];

    // sprintf(calculado, "%.15f", pi);

    // int count = 0;
    // for (int i = 2; i < 18; i++){
    //     if (calculado[i] == real[i]) {
    //         count++;
    //     }
    //     else {
    //         break;
    //     }
    // }

    // printf("Casas decimais iguais: %d\n", count);

    // procurar algum caso real que precise de maior precisão assim como o cálculo de pi.

    return 0;
}