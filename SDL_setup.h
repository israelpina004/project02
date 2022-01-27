#include <SDL2/SDL.h>
#include "SDL_global_variables.h"
#include <SDL2/SDL_ttf.h>

#ifndef SDL_setup_h
#define SDL_setup_h

struct WindowInfo
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *Sans;
};

struct Coords
{
    int x, y;
};

struct WindowInfo
SDL_setup();

#endif