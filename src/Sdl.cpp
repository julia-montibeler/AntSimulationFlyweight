#include "Sdl.h"
#include <SDL2/SDL.h>
#include "Janela.h"
#include <SDL2/SDL_thread.h>

#include <iostream>
using namespace std;

Sdl* Sdl::sdl= nullptr;

//Construtor
Sdl::Sdl(){

    //Iniciar sistema de video
    //Se retornar menor que 0 exibirá um erro
    if( SDL_Init(SDL_INIT_VIDEO) < 0)
        cout << "SDL não pode ser iniciado: " << SDL_GetError();

    else
        cout << "Sistemas de video inicializados\n";
}

//Destrutor
Sdl::~Sdl()
{
    //Fechar SDL
    SDL_Quit();
}

Sdl *Sdl::criar()
{
    if (sdl==nullptr)
        sdl = new Sdl();
    return sdl;
}

int Sdl::handleEvents()
{
    while( SDL_PollEvent( &eventHandler ) != 0 ) {

        //User requests quit
        if ( eventHandler.type == SDL_QUIT )
            return 0;

        else if ( eventHandler.type == SDL_MOUSEBUTTONDOWN)
            if(eventHandler.button.button == SDL_BUTTON_LEFT)
                return 2;
            else if(eventHandler.button.button == SDL_BUTTON_RIGHT)
                return 3;
            
    }
    return 1;
}
