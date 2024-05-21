#include "Formigueiro.h"

Formigueiro::Formigueiro(int x, int y, int w, int h) : Objeto(x, y, w, h) {

    type = Type::formigueiro;
    qtd_comida = 0;

}