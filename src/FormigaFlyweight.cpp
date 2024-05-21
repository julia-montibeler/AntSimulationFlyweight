#include "FormigaFlyweight.h"


FormigaFlyweight::FormigaFlyweight(int distVisao, int angVisao, Renderer* r) {
    this->distVisao = distVisao;
    this->angVisao = angVisao;

    SDL_Surface* formiga_sur = IMG_Load("formiga.png");
    this->formiga_tex = SDL_CreateTextureFromSurface(r->get_sdlRenderer(), formiga_sur);

    //SDL_FreeSurface(formiga_sur);
}

int FormigaFlyweight::getAngVisao(){
    return angVisao;
}


int FormigaFlyweight::getDistVisao(){
    return distVisao;
}

SDL_Texture* FormigaFlyweight::getFormigaTexture(){
    return formiga_tex;
}
