#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>


class Renderer
{
public:
    
    //Construtor
    Renderer(SDL_Window *sdlWindow);

    // Retorna Objeto do SDL
    SDL_Renderer *get_sdlRenderer() const;

    // Desenha ponto na Tela na posição indicada
    void drawPoint(int x, int y);
    
    // Desenha linha na Tela a partir dos pontos indicados
    void drawLine(int x1, int y1, int x2, int y2);

    // Desenha retangulo na Tela a partir de um objeto SDL_Rect
    void drawRect(const SDL_Rect *rect);

    void fillRect(const SDL_Rect *rect);

    // Muda cor dos Itens a serem desenhados
    void changeColor(int r, int g, int b, int a);

    // Atualiza a Tela
    void update();

    // Limpa a Tela
    void clear();

private:

    // Objeto do SDL utilizado para desenhar na Tela
    SDL_Renderer *sdlRenderer = nullptr;

    // Variaveis que indicam cor usada no momento
    int r, g, b, a;
};

#endif