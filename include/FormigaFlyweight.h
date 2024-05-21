#ifndef FORMIGA_FLYWEIGHT
#define FORMIGA_FLYWEIGHT

#include <SDL2/SDL_image.h>
#include "Renderer.h"

class FormigaFlyweight {

    private:
        // Campo de visão
        int distVisao = 30;
        int angVisao = 180;

        // Textura Formiga
        SDL_Texture* formiga_tex;

    public:
        FormigaFlyweight(int distVisao, int angVisao, Renderer* r);

        int getDistVisao();
        int getAngVisao();
        SDL_Texture* getFormigaTexture();
};

#endif