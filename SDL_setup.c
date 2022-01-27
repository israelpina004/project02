#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "SDL_setup.h"
#include "SDL_global_variables.h"
#include "SDL_functions.h"

struct WindowInfo SDL_setup()
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    struct WindowInfo info;
    info.renderer = renderer;
    info.window = window;

    printf("finished init window\n");

    // + 1 so that the last grid lines fit in the screen.
    int window_width = (grid_cell_size * 2) + (grid_width * grid_cell_size + 2) + (grid_cell_size * 3) + (grid_width * grid_cell_size + 2) + (grid_cell_size * 2);
    int window_height = (grid_height * grid_cell_size) + (grid_cell_size * 2) + 1;

    // retutns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        exit(1);
    }

    if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &info.window,
                                    &info.renderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer: %s", SDL_GetError());
        exit(1);
    }

    SDL_SetWindowTitle(info.window, "Battle Ship");

    //font
    if (TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }
    TTF_Font *Sans = TTF_OpenFont("static/OpenSans/OpenSans-Light.ttf", 24);

    if (Sans == NULL)
    {
        printf("TTF_Openfont: %s\n", TTF_GetError());
        exit(2);
    }

    info.Sans = Sans;

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Texture *letters[grid_width];

    SDL_Texture *numbers[grid_height];

    SDL_Rect Message_rect = {
        .x = 0,                  //controls the rect's x coordinate
        .y = 0,                  // controls the rect's y coordinte
        .w = grid_cell_size / 2, // controls the width of the rect
        .h = grid_cell_size,
    };

    //creating letter textures
    for (int l = 0; l < grid_width; l++)
    {
        char temp = (char)(l + 65);
        SDL_Surface *temp_surface = TTF_RenderText_Solid(info.Sans, &temp, grid_cursor_color);
        letters[l] = SDL_CreateTextureFromSurface(info.renderer, temp_surface);
    }

    //creating number textures
    for (int l = 0; l < grid_height; l++)
    {
        char temp = l + '0';
        SDL_Surface *temp_surface = TTF_RenderText_Solid(info.Sans, &temp, grid_cursor_color);
        numbers[l] = SDL_CreateTextureFromSurface(info.renderer, temp_surface);
    }

    // Draw grid background. non static
    SDL_SetRenderDrawColor(info.renderer, grid_background.r, grid_background.g,
                           grid_background.b, grid_background.a);
    SDL_RenderClear(info.renderer);

    // Draw player 1 grid lines.
    SDL_SetRenderDrawColor(info.renderer, grid_line_color.r, grid_line_color.g,
                           grid_line_color.b, grid_line_color.a);

    for (int x = player_1_grid; x < 1 + player_1_grid + grid_width * grid_cell_size;
         x += grid_cell_size)
    {
        SDL_RenderDrawLine(info.renderer, x, grid_cell_size, x, grid_cell_size + grid_cell_size * grid_height);
    }

    for (int y = grid_cell_size; y < 1 + grid_height * grid_cell_size + grid_cell_size;
         y += grid_cell_size)
    {
        SDL_RenderDrawLine(info.renderer, player_1_grid, y, player_1_grid + grid_cell_size * grid_width, y);
    }

    // Draw player 2 grid lines.
    for (int x = player_2_grid; x < 1 + player_2_grid + grid_width * grid_cell_size;
         x += grid_cell_size)
    {
        SDL_RenderDrawLine(info.renderer, x, grid_cell_size, x, grid_cell_size + grid_cell_size * grid_height);
    }

    for (int y = grid_cell_size; y < 1 + grid_height * grid_cell_size + grid_cell_size;
         y += grid_cell_size)
    {
        SDL_RenderDrawLine(info.renderer, player_2_grid, y, player_2_grid + grid_cell_size * grid_width, y);
    }

    for (int x = 0; x < grid_width; x++)
    {
        //draw grid 1 letters
        Message_rect.x = (x * grid_cell_size) + player_1_grid + grid_cell_size / 4;
        Message_rect.y = 0;
        SDL_RenderCopy(info.renderer, letters[x], NULL, &Message_rect);

        //draw grid 2 letters
        Message_rect.x = (x * grid_cell_size) + player_2_grid + grid_cell_size / 4;
        Message_rect.y = 0;
        SDL_RenderCopy(info.renderer, letters[x], NULL, &Message_rect);
    }

    for (int y = 0; y < grid_height; y++)
    {
        //draw grid 1 numbers
        Message_rect.x = grid_border_left;
        Message_rect.y = (y * grid_cell_size) + grid_cell_size + grid_cell_size / 4;
        SDL_RenderCopy(info.renderer, numbers[y], NULL, &Message_rect);

        //draw grid 2 numbers
        Message_rect.x = grid_border2_left;
        Message_rect.y = (y * grid_cell_size) + grid_cell_size + grid_cell_size / 4;
        SDL_RenderCopy(info.renderer, numbers[y], NULL, &Message_rect);
    }

    SDL_RenderPresent(info.renderer);

    return info;
}