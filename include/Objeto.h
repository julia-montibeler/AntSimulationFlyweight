#ifndef OBJETO_H
#define OBJETO_H

#include <SDL2/SDL.h>
#include "Renderer.h"
#include "Ponto.h"

class Objeto : public Ponto {


    protected:
        
        // Largura e Altura do Objeto
        int width;
        int height;

        // Retangulo do SDL, usado para exibir o Objeto na Tela
        SDL_Rect rect;

    public:

        // Construtor
        Objeto(int x, int y, int w, int h);

        //~Objeto();
        
        // Desenha o Objeto na Tela
        void draw(Renderer *r);

        // Retorna o Retangulo do SDL
        const SDL_Rect* get_rect();

        // Verifica colisao com outro Objeto
        bool verf_colisao(Objeto *obj);

        int get_width();
        int get_height();
};


#endif
