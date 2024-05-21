#include "FuncoesAuxiliares.h"

#include <stdio.h>
#include <vector>

#define PI 3.14159265

int gerar_random(int ini, int fim) {

    int tam = fim - ini + 1;

    int random = ((rand() % tam) + ini);

    return random;

}

float conv_radianos(int angulo) {

    return (angulo * PI/180);

}
