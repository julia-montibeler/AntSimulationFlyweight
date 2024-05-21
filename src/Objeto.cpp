#include "Objeto.h"

#include <iostream>
using namespace std;

Objeto::Objeto(int x, int y, int w, int h) : Ponto(x , y){

    width = w;
    height = h;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    type = Type::objeto;

}

const SDL_Rect* Objeto::get_rect() {

    return &rect;

}

void Objeto::draw(Renderer *r) {

    r->drawRect(&rect);
    r->fillRect(&rect);

}

int Objeto::get_width() {

    return width;

}

int Objeto::get_height() {

    return height;

}