/*Not finished, needs:
 -error checking (i.e. if coordinates called for are valid or if the opponent has already shot there)
 -win condition checking
 -checking for which ships have sunk
*/

#include "networking.h"
#include "setup.h"
#include "game.h"

int game(int user_board[10][10], int attack_board[10][10], int socket_fd) {
  int i, j;
  char s[100];

  printf("\nYour attack board:\n");
  for(i = 0; i < 10; i++) {
    for(j = 0; j < 10; j++) {
      printf("%d ", attack_board[j][i]);
    }
    printf("\n");
  }

  printf("\nEnter a message: ");
  fgets(s, 100, stdin);
  write(socket_fd, s, sizeof(s));
  if(read(socket_fd, s, sizeof(s))<=0)
  {
    printf("[Client] Failed to read.\n");
  }

  int x, y;
  if(s[0] == ':') {
    x = letter_to_num(s[1]);
    y = letter_to_num(s[2]);

    if(user_board[x][y] != 0) {
      strncpy(s, ship(user_board[x][y]), 100);
    }

    user_board[x][y] = 6;
    attack_board[x][y] = 6;
  }

}

char* ship(int id) {
  switch(id) {
    case 1:
      return "You've hit the carrier!\n";
      break;
    case 2:
      return "You've hit the battleship!\n";
      break;
    case 3:
      return "You've hit the cruiser!\n";
      break;
    case 4:
      return "You've hit the submarine!\n";
      break;
    case 5:
      return "You've hit the destroyer!\n";
      break;
    case 6:
      return "You already shot there, try another square.\n";
      break;
    default:
      return "Miss!";
      break;
  }
}
