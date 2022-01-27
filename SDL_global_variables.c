#include <SDL2/SDL.h>

const int grid_cell_size = 36;
const int grid_width = 10;
const int grid_height = 10;

//starting positions
const int grid_padding_left = 0;

const int grid_border_left = grid_padding_left + grid_cell_size;

const int player_1_grid = grid_border_left + grid_cell_size;

const int grid_border_right = player_1_grid + (grid_width * grid_cell_size) + 2; //+2 to account for line length

const int grid_padding_middle = grid_border_right + grid_cell_size;

const int grid_border2_left = grid_padding_middle + grid_cell_size;

const int player_2_grid = grid_border2_left + (grid_cell_size);

const int grid_border2_right = player_2_grid + (grid_width * grid_cell_size) + 2;

const int grid_padding_right = grid_border2_right + grid_cell_size;

// Dark theme.
const SDL_Color grid_background = {22, 22, 22, 255};         // Barely Black
const SDL_Color grid_line_color = {44, 44, 44, 255};         // Dark grey
const SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255}; //light gray
const SDL_Color grid_cursor_color = {255, 255, 255, 255};    // White
const SDL_Color grid_border_color = {173, 216, 230, 255};    //light blue

//ship colors
extern const SDL_Color carier_color = {78, 138, 164, 255};      //Dark Blue
extern const SDL_Color battleship_color = {255, 125, 117, 255}; //orange
extern const SDL_Color cruiser_color = {242, 255, 165, 255};    //yellow
extern const SDL_Color sub_color = {124, 218, 184, 255};        //green
extern const SDL_Color destroyer_color = {7193, 204, 255, 255}; //soft purple

//board colors
extern const SDL_Color ship_hit = {238, 101, 135, 255}; //soft red
extern const SDL_Color missed = grid_cursor_ghost_color;
