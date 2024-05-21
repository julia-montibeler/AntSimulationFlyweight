#ifndef JANELA_H
#define JANELA_H

#include "Sdl.h"
#include "Renderer.h"

#include <SDL2/SDL.h>

class Janela
{

public:

    // Construtor
    Janela(const char *title, int w, int h);

    // Destrutor
    ~Janela();

    // Getter para sdlWindow
    SDL_Window *get_sdlWindow();

    // Getter para width
    int get_width();

    // Getter para height
    int get_height();

    // Função principal de loop
    void loop();

private:

    // Ponteiro para Objeto do SDL
    SDL_Window *sdlWindow = nullptr;

    // Largura e Altura
    int width = 800;
    int height = 600;

    // Titulo da Janela
    char *title;

    // Ponteiro para objeto usado para o basico do SDL
    Sdl *sdl;

    // Ponteiro para objeto usado para rendenizar Objetos na Tela
    Renderer *renderer;
    
};

#endif