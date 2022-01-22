int game(int user_board[10][10], int attack_board[10][10], int socket_fd, int order);
void attack_check(char* s, int attack_board[10][10]);
char* ship(int id);
char* sink(int id, int user_board[10][10]);
int win_lose(int user_board[10][10]);
