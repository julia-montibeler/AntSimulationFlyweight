#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>

class Sdl
{
    public:    

        // Destrutor
        ~Sdl();

        // Estado atual das Teclas
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

        // Metodo estatico usado para garantir a existencia de apenas UM objeto desta classe
        static Sdl *criar();

        // Função para administrar Eventos do Teclado e Mouse
        int handleEvents();
    

    private:

        // Construtor Privado, só é chamado pelo metodo criar, impendindo a criação de mais de um Objeto desta classe
        Sdl();

        // Variavel que faz referencia ao objeto desta classe
        static Sdl* sdl;

        // Objeto do SDL usado para Administrar eventos de teclado e mouse do SDL
        SDL_Event eventHandler;
};

#endif