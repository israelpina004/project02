/*Not finished, needs:
 -error checking (i.e. if coordinates called for are valid or if the opponent has already shot there)
 -win condition checking
 -checking for which ships have sunk
*/

#include "networking.h"
#include "setup.h"
#include "game.h"

static void sighandler(int signo){
  if(signo == SIGINT ){
    printf("\nPlayer has left, exiting...\n");
    exit(0);
  }
}

int game(int user_board[10][10], int attack_board[10][10], int socket_fd, int order) {
  int i, j, x, y;
  char s[100];
  char temp[100];

  if(!order) {
    printf("\nP1: ");
    while(1){
      fgets(s, 100, stdin);
      if(isalpha(s[0])) {
        char c;
        sscanf(s, "%c%d", &c, &y);
        y -= 1;
        x = letter_to_num(c);
        if(attack_check(x, y, attack_board)){
          printf("ERROR: Enter valid coordinates.\n");
        }else{break;}
      }else{
        printf("Attack format: \"(Letter)(Number)\" \n Enter coordinates: ");
      }
    }

    write(socket_fd, s, sizeof(s));
    read(socket_fd, s, 100);
    if(strcmp(s, "Miss!\n")==0) {
      attack_board[x][y] = 7;
    }
    printf("%s\n", s);
    read(socket_fd, s, 100);
    printf("%s\n", s);
    read(socket_fd, s, 100);
    printf("%s\n", s);
    if(strcmp(s, " ")){
      return 1;
    }
    printf("Your attack board:\n");
    for(i = 0; i < 10; i++) {
      for(j = 0; j < 10; j++) {
        printf("%d ", attack_board[j][i]);
      }
      printf("\n");
    }
  }

  printf("Waiting for opponent to attack ...\n");
  if(read(socket_fd, s, sizeof(s))<=0)
  {
    sighandler(SIGINT);
  }
  else if(isalpha(s[0])) {
    char c;
    int y;
    sscanf(s, "%c%d", &c, &y);
    y -= 1;
    int x = letter_to_num(c);

    int id = user_board[x][y];

    strncpy(temp, ship(id), 100);
    write(socket_fd, temp, sizeof(temp));
    if(strcmp(temp, "Miss!\n")) {
      user_board[x][y] = 6;
      printf("It was a hit!\n");
    }else{user_board[x][y] = 7; printf("It was a miss!\n");}
    strncpy(temp, sink(id, user_board), 100);
    write(socket_fd, temp, sizeof(temp));
  }

  strncpy(temp, "You win!", sizeof(temp));
  if(win_lose(user_board) != 0) {
    write(socket_fd, temp, sizeof(temp));
    printf("\nYou lose.\n");
    return 1;
  }else{strncpy(temp, " ", sizeof(temp)); write(socket_fd, temp, sizeof(temp));}

  printf("\nYour board:\n");
  for(i = 0; i < 10; i++) {
    for(j = 0; j < 10; j++) {
      printf("%d ", user_board[j][i]);
    }
    printf("\n");
  }

  if(order) {
    printf("\nP2: ");
    while(1){
      fgets(s, 100, stdin);
      if(isalpha(s[0])) {
        char c;
        sscanf(s, "%c%d", &c, &y);
        y -= 1;
        x = letter_to_num(c);
        if(attack_check(x, y, attack_board)){
          printf("ERROR: Enter valid coordinates.\n");
        }else{break;}
      }else{
        printf("Attack format: \"(Letter)(Number)\" \nEnter coordinates: ");
      }
    }

    write(socket_fd, s, sizeof(s));
    printf("Sent attack, waiting for hit or miss ...\n");
    read(socket_fd, s, 100);
    if(strcmp(s, "Miss!\n")==0) {
      attack_board[x][y] = 7;
    }
    printf("%s\n", s);
    read(socket_fd, s, 100);
    printf("%s\n", s);
    read(socket_fd, s, 100);
    printf("%s\n", s);
    if(strcmp(s, " ")){
      return 1;
    }
    printf("Your attack board:\n");
    for(i = 0; i < 10; i++) {
      for(j = 0; j < 10; j++) {
        printf("%d ", attack_board[j][i]);
      }
      printf("\n");
    }
  }
  return 0;
}

int attack_check(int x, int y, int attack_board[10][10]) {
    if(x < 0 || x > 9 || y < 0 || y > 9) {
      return 1;
    }
    else if(attack_board[x][y] == 6 || attack_board[x][y] == 7) {
      return 1;
    }
    else {
      attack_board[x][y] = 6;
      return 0;
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
    case 5:
      return "You've sunk my destroyer!\n";
      break;
    default:
      return "...\n";
      break;
  }

  return 0;
}

int win_lose(int user_board[10][10]) {
  int k, m;
  for(m = 0; m < 10; m++) {
    for(k = 0; k < 10; k++) {
      if(user_board[k][m] != 0 && user_board[k][m] != 6 && user_board[k][m] != 7) {
          return 0;
      }
    }
  }
  return -1;
}
