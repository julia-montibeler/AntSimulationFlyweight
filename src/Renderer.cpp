#include "Renderer.h"
#include "Janela.h"

#include <SDL2/SDL.h>

using namespace std;

Renderer::Renderer(SDL_Window *sdlWindow)
{

    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);

};

SDL_Renderer *Renderer::get_sdlRenderer() const
{
    return sdlRenderer;
}

void Renderer::changeColor(int r, int g, int b, int a)
{
    Renderer::r = r;
    Renderer::g = g;
    Renderer::b = b;
    Renderer::a = a;
    SDL_SetRenderDrawColor(sdlRenderer, r, g, b, a);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(sdlRenderer, x1, y1, x2, y2);
}

void Renderer::drawPoint(int x, int y)
{
    SDL_RenderDrawPoint(sdlRenderer, x, y);
}

void Renderer::drawRect(const SDL_Rect *rect) {

    SDL_RenderDrawRect(sdlRenderer, rect);

}

void Renderer::fillRect(const SDL_Rect *rect) {

    SDL_RenderFillRect(sdlRenderer, rect);

}

void Renderer::update()
{
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
    SDL_RenderPresent(sdlRenderer);
    SDL_SetRenderDrawColor(sdlRenderer, r, g, b, a);
}

void Renderer::clear()
{
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(sdlRenderer);
}
