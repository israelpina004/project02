#include "SDL_global_variables.h"
#include "SDL_setup.h"
#include "SDL_functions.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Coords render_ship(struct WindowInfo info, int ship_size, int board[10][10])
{
    //direction 0=right 1=down 2=left 3=up
    int ship_dir = 0;

    // Place the ship in the middle of the screen.
    SDL_Rect grid_cursor = {
        .x = (grid_width - 1) / 2 * grid_cell_size,
        .y = (grid_height - 1) / 2 * grid_cell_size,
        .w = grid_cell_size,
        .h = grid_cell_size,
    };

    //ship blocks
    SDL_Rect ship_block_rect = {
        .x = (grid_width - 1) / 2 * grid_cell_size,
        .y = (grid_height - 1) / 2 * grid_cell_size, // controls the rect's y coordinte
        .w = grid_cell_size,                         // controls the width of the rect
        .h = grid_cell_size,
    };

    // The cursor ghost is a cursor that always shows in the cell below the
    // mouse cursor.
    SDL_Rect grid_cursor_ghost = {grid_cursor.x, grid_cursor.y, grid_cell_size,
                                  grid_cell_size};

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

    SDL_bool quit = SDL_FALSE;
    SDL_bool mouse_active = SDL_FALSE;
    SDL_bool mouse_hover = SDL_FALSE;

    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_s:;
                    int x = ((grid_cursor.x - player_1_grid) / grid_cell_size);
                    int y = (grid_cursor.y - grid_cell_size) / grid_cell_size;
                    struct Coords c = {
                        .x = x,
                        .y = y,
                    };
                    printf("x - %d, y - %d \n", x, y);
                    return c;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:;
                int grid_cursor_ghost_x_coord = (event.motion.x / grid_cell_size) * grid_cell_size;
                int grid_cursor_ghost_y_coord = (event.motion.y / grid_cell_size) * grid_cell_size;
                //inside grid check
                //y check
                if (grid_cursor_ghost_y_coord >= grid_cell_size && grid_cursor_ghost_y_coord <= grid_cell_size * grid_height)
                {
                    //xcheck
                    if (grid_cursor_ghost_x_coord <= grid_border_right - (grid_cell_size * ship_size) && grid_cursor_ghost_x_coord >= player_1_grid)
                    {
                        grid_cursor.x = grid_cursor_ghost_x_coord;
                        grid_cursor.y = grid_cursor_ghost_y_coord;
                    }
                }

                break;
            case SDL_MOUSEMOTION:;
                int xcoords = (event.motion.x / grid_cell_size) * grid_cell_size;
                int ycoords = (event.motion.y / grid_cell_size) * grid_cell_size;

                if (xcoords <= grid_border_right - grid_cell_size && xcoords >= player_1_grid && ycoords >= grid_cell_size && ycoords <= grid_cell_size * grid_height)
                {
                    grid_cursor_ghost.x = xcoords;
                    grid_cursor_ghost.y = ycoords;
                }

                if (!mouse_active)
                    mouse_active = SDL_TRUE;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouse_hover)
                    mouse_hover = SDL_TRUE;
                else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouse_hover)
                    mouse_hover = SDL_FALSE;
                break;
            case SDL_QUIT:
                quit = SDL_TRUE;
                break;
            }
        }

        //drawing background
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

        //draw existing ships
        for (int x = 0; x < 10; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                switch (board[x][y])
                {

                //carrier ships
                case 1:
                    SDL_SetRenderDrawColor(info.renderer, carier_color.r,
                                           carier_color.g, carier_color.b,
                                           carier_color.a);

                    struct Coords carrier_coords =
                        {
                            .x = x * grid_cell_size + player_1_grid,
                            .y = y * grid_cell_size + grid_cell_size,
                        };

                    ship_block_rect.x = carrier_coords.x;
                    ship_block_rect.y = carrier_coords.y;

                    SDL_RenderFillRect(info.renderer, &ship_block_rect);
                    break;

                //battleship
                case 2:
                    SDL_SetRenderDrawColor(info.renderer, battleship_color.r,
                                           battleship_color.g, battleship_color.b,
                                           battleship_color.a);

                    struct Coords battleship_coords =
                        {
                            .x = x * grid_cell_size + player_1_grid,
                            .y = y * grid_cell_size + grid_cell_size,
                        };

                    ship_block_rect.x = battleship_coords.x;
                    ship_block_rect.y = battleship_coords.y;

                    SDL_RenderFillRect(info.renderer, &ship_block_rect);
                    break;
                //cruiser
                case 3:
                    SDL_SetRenderDrawColor(info.renderer, cruiser_color.r,
                                           cruiser_color.g, cruiser_color.b,
                                           cruiser_color.a);

                    struct Coords cruiser_coords =
                        {
                            .x = x * grid_cell_size + player_1_grid,
                            .y = y * grid_cell_size + grid_cell_size,
                        };

                    ship_block_rect.x = cruiser_coords.x;
                    ship_block_rect.y = cruiser_coords.y;

                    SDL_RenderFillRect(info.renderer, &ship_block_rect);
                    break;
                //sub
                case 4:
                    SDL_SetRenderDrawColor(info.renderer, sub_color.r,
                                           sub_color.g, sub_color.b,
                                           sub_color.a);

                    struct Coords sub_coords =
                        {
                            .x = x * grid_cell_size + player_1_grid,
                            .y = y * grid_cell_size + grid_cell_size,
                        };

                    ship_block_rect.x = sub_coords.x;
                    ship_block_rect.y = sub_coords.y;

                    SDL_RenderFillRect(info.renderer, &ship_block_rect);
                    break;

                //destroyer
                case 5:
                    SDL_SetRenderDrawColor(info.renderer, destroyer_color.r,
                                           destroyer_color.g, destroyer_color.b,
                                           destroyer_color.a);

                    struct Coords destroyer_coords =
                        {
                            .x = x * grid_cell_size + player_1_grid,
                            .y = y * grid_cell_size + grid_cell_size,
                        };

                    ship_block_rect.x = destroyer_coords.x;
                    ship_block_rect.y = destroyer_coords.y;

                    SDL_RenderFillRect(info.renderer, &ship_block_rect);
                    break;
                }
            }
        }

        if (ship_dir % 2 == 0)
        {
            grid_cursor.w = grid_cell_size * ship_size;
            grid_cursor.h = grid_cell_size;
        }
        else
        {
            grid_cursor.h = grid_cell_size * ship_size;
            grid_cursor.w = grid_cell_size;
        }

        // Draw grid ghost cursor.
        if (mouse_active && mouse_hover)
        {
            SDL_SetRenderDrawColor(info.renderer, grid_cursor_ghost_color.r,
                                   grid_cursor_ghost_color.g,
                                   grid_cursor_ghost_color.b,
                                   grid_cursor_ghost_color.a);
            SDL_RenderFillRect(info.renderer, &grid_cursor_ghost);
        }

        // Draw grid cursor.
        SDL_SetRenderDrawColor(info.renderer, grid_cursor_color.r,
                               grid_cursor_color.g, grid_cursor_color.b,
                               grid_cursor_color.a);
        SDL_RenderFillRect(info.renderer, &grid_cursor);

        SDL_RenderPresent(info.renderer);
    }
}