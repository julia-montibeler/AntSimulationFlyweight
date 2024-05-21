#include "Janela.h"
#include "FuncoesAuxiliares.h"
#include "Formiga.h"
#include "Feromonio.h"
#include "Grid.h"
#include "Persistencia.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include <iostream>
using namespace std;
#define PI 3.14159265
#define QTD_FORMIGAS 2000

// Construtor
Janela::Janela(const char *titulo, int w, int h)
{
    sdl = Sdl::criar();

    title = title;
    width = w;
    height = h;

    sdlWindow = SDL_CreateWindow(titulo, 0, 0, w, h, SDL_WINDOW_SHOWN);
    renderer = new Renderer(sdlWindow);
}

// Destrutor
Janela::~Janela()
{

    SDL_DestroyWindow(sdlWindow);
}

// Retornar janela sdl
SDL_Window *Janela::get_sdlWindow()
{
    return sdlWindow;
}

int Janela::get_height()
{
    return height;
}

int Janela::get_width()
{
    return width;
}

void Janela::loop()
{  

    int mouseX = 0;
    int mouseY = 0;

    bool running = 1;

    Grid *grid = new Grid(800, 600);

    // OBSTACULOS armazenados usando persistencia
    int cont=qtdObj();
    int aux=0, aux2;
    int *dados = lerDados();

    while (aux<cont)
    {   
        grid->inserir(new Objeto(dados[aux], dados[aux+1], 40, 40));
        aux+=2;
        aux2++;
    }
    
    // FORMIGUEIRO / COMIDA / FORMIGA
    grid->inserir(new Formigueiro(50, 50, 30, 30));
    grid->inserirCom(new Objeto(700, 500, 30, 30));
    grid->inserirFormigas(QTD_FORMIGAS, renderer);

    while (running)
    {   
        
        renderer->clear();

        switch (sdl->handleEvents())
        {
        case 0:
            running = 0;
            break;

        case 1: break;

        case 2:

            SDL_GetMouseState(&mouseX, &mouseY);
            grid->inserir(new Objeto(mouseX - 20, mouseY - 20, 40, 40));

            break;
        
        case 3:

            SDL_GetMouseState(&mouseX, &mouseY);
            grid->removeObjeto(mouseX, mouseY);
            break;
        
        }

        grid->exibir(renderer);

        renderer->update();

        //SDL_Delay(0);
    }

    grid->salvarDados();
}
