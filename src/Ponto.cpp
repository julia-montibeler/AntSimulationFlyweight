#include "Ponto.h"
#include "Grid.h"

Ponto::Ponto(int x, int y) {

    pos_x = x;
    pos_y = y;

}

Ponto::~Ponto() {}

int Ponto::get_pos_x() {

    return pos_x;

}
int Ponto::get_pos_y() {

    return pos_y;

}

void Ponto::draw(Renderer *r) {

    r->drawPoint(pos_x, pos_y);

}