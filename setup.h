#include <ctype.h>

int setup(int user_board[10][10]);
int carrier(int board[10][10]);
int battleship(int board[10][10], int coords[4][2]);
int cruiser(int board[10][10], int coords[3][2]);
int sub(int board[10][10], int coords[3][2]);
int destroyer(int board[10][10], int coords[2][2]);
int error_check(int x, int y, int board[10][10]);
int letter_to_num(char letter);
