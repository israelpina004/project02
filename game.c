/*Not finished, needs:
 -error checking (i.e. if coordinates called for are valid or if the opponent has already shot there)
 -win condition checking
 -checking for which ships have sunk
*/

#include "networking.h"
#include "setup.h"
#include "game.h"

int game(int user_board[10][10], int attack_board[10][10], int socket_fd, int order) {
  int i, j;
  char s[100];

  printf("\nYour attack board:\n");
  for(i = 0; i < 10; i++) {
    for(j = 0; j < 10; j++) {
      printf("%d ", attack_board[j][i]);
    }
    printf("\n");
  }

  if(!order) {
    printf("\nP1: ");
    fgets(s, 100, stdin);
    attack_check(s, attack_board);
    printf("frefrfr\n");

    write(socket_fd, s, sizeof(s));
    printf("Sent attack, waiting for hit or miss ...\n");
    read(socket_fd, s, sizeof(s));

    printf("%s\n", s);
  }

  printf("Waiting for opponent to attack ...\n");
  if(read(socket_fd, s, sizeof(s))<=0)
  {
    printf("Failed to read.\n");
  }
  else if(s[0] == ':') {
    char c;
    int y;
    sscanf(s, ":%c%d", &c, &y);
    y -= 1;
    int x = letter_to_num(c);

    int id = user_board[x][y];

    write(socket_fd, ship(id), sizeof(ship(id)));
    if(strcmp(ship(id), "Miss!\n")) {
      user_board[x][y] = 6;
      write(socket_fd, sink(id, user_board), sizeof(sink(id, user_board)));
    }

    user_board[x][y] = 6;
  }
  else {
    printf("%s\n", s);
  }

  if(win_lose(user_board) != 0) {
    char* msg = "You win!";
    write(socket_fd, msg, sizeof(msg));
    printf("You lose.\n");

    return 1;
  }

  printf("\nYour board:\n");
  for(i = 0; i < 10; i++) {
    for(j = 0; j < 10; j++) {
      printf("%d ", user_board[j][i]);
    }
    printf("\n");
  }

  if(order) {
    printf("\nP2: ");
    fgets(s, 100, stdin);
    attack_check(s, attack_board);

    write(socket_fd, s, sizeof(s));
    read(socket_fd, s, sizeof(s));

    printf("%s\n", s);
  }

  return 0;
}

void attack_check(char* s, int attack_board[10][10]) {
  if(s[0] == ':') {
    char c;
    int y;
    sscanf(s, ":%c%d", &c, &y);
    y -= 1;
    int x = letter_to_num(c);

    if(x < 0 || x > 9 || y < 0 || y > 9) {
      printf("ERROR: Enter valid coordinates.\n");
      fgets(s, 100, stdin);
      attack_check(s, attack_board);
    }
    else if(attack_board[x][y] == 6) {
      printf("ERROR: Enter valid coordinates.\n");
      fgets(s, 100, stdin);
      attack_check(s, attack_board);
    }
    else {
      attack_board[x][y] = 6;
    }
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
    default:
      return "Miss!\n";
      break;
  }
}

char* sink(int id, int user_board[10][10]) {
  int k, m;
  for(m = 0; m < 10; m++) {
    for(k = 0; k < 10; k++) {
      if(user_board[k][m] == id) {
        return "...\n";
      }
    }
  }

  switch(id) {
    case 1:
      return "You've sunk my carrier!\n";
      break;
    case 2:
      return "You've sunk my battleship!\n";
      break;
    case 3:
      return "You've sunk my cruiser!\n";
      break;
    case 4:
      return "You've sunk my submarine!\n";
      break;
    default:
      return "You've sunk my destroyer!\n";
      break;
  }

  return 0;
}

int win_lose(int user_board[10][10]) {
  int k, m;
  for(m = 0; m < 10; m++) {
    for(k = 0; k < 10; k++) {
      if(user_board[k][m] != 0 || user_board[k][m] != 6) {
          return 0;
      }
    }
  }
  return -1;
}
