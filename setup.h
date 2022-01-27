#include <ctype.h>
#include "SDL_setup.h"

int setup(int user_board[10][10], int attack_board[10][10], struct WindowInfo info);
int carrier(int board[10][10], struct WindowInfo info);
int battleship(int board[10][10], int coords[4][2], struct WindowInfo info);
int cruiser(int board[10][10], int coords[3][2], struct WindowInfo info);
int sub(int board[10][10], int coords[3][2], struct WindowInfo info);
int destroyer(int board[10][10], int coords[2][2], struct WindowInfo info);
int error_check(int x, int y, int board[10][10]);
int letter_to_num(char letter);
