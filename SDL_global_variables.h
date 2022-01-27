#include <SDL2/SDL.h>

extern const int grid_cell_size;
extern const int grid_width;
extern const int grid_height;

//starting positions
extern const int grid_padding_left;

extern const int grid_border_left;

extern const int player_1_grid;

extern const int grid_border_right; //+2 to account for line length

extern const int grid_padding_middle;

extern const int grid_border2_left;

extern const int player_2_grid;

extern const int grid_border2_right;

extern const int grid_padding_right;
// Dark theme.
extern const SDL_Color grid_background;
extern const SDL_Color grid_line_color;
extern const SDL_Color grid_cursor_ghost_color;
extern const SDL_Color grid_cursor_color;
extern const SDL_Color grid_border_color;

//ship colors
extern const SDL_Color carier_color;
extern const SDL_Color battleship_color;
extern const SDL_Color cruiser_color;
extern const SDL_Color sub_color;
extern const SDL_Color destroyer_color;

//board colors
extern const SDL_Color ship_hit;
extern const SDL_Color missed;