#include "networking.h"
#include "setup.h"
#include "game.h"

static void sighandler(int signo){
  if(signo == SIGINT ){
    printf("\nPlayer has left, exiting...\n");
    exit(0);
  }
}

int main(){
  signal(SIGINT, sighandler);
  int user_board[10][10];
  int attack_board[10][10];
  char a[10];
  char s[50];
  int d=-1;
  int socket_fd;
  printf("Welcome to Battleship v1.0! \nPlease enter whether you want to: \n Create a Game [0] \n Join a Game [1] \n Help [2] \n\n");
  printf("WARNING: The host should NOT ctrl-C until the other player has left. ");
  printf("This will prevent host-client connections in future games. ");
  printf("The game will have to be recompiled to be successfully ran again.\n");
  while(1){
    fgets(a, 10 ,stdin);
    if(strcmp(a,"0\n")==0){printf("Creating a Game!\n"); d=0; break;}
    else if(strcmp(a,"1\n")==0){printf("Joining a Game!\n"); d=1; break;}
    else if(strcmp(a, "2\n") == 0) {
      printf("\nThe objective of the game is to sink all five of your opponent's ships first.\n");
      printf("Before each of you begins, you'll each have to place these ships on your virtual board.\n");
      printf("\nYou will be prompted to input coordinates in this format: ':(Letter)(Number)'\n");
      printf("How ship placements will work is that these coordinates are treated like the \"head\" of the ship.\n");
      printf("Thus, when you are prompted to place each ship either horizontally left or right or vertically up or down, ");
      printf("all the other coordinates will be left, right, up, or down from the one you specify.\n\n");
      printf("Good luck and godspeed, admiral.\n");
    }
    else{printf("Invalid response, please try again: \n ");}
  }
  if(d){
    socket_fd=client_setup();
    printf("Connection Successful! \n");
    printf("Entering preparatory phase!\n");
    setup(user_board, attack_board);
    while(1){
      if(game(user_board, attack_board, socket_fd, 1)) {
        break;
      }
    }
    printf("Thank you for playing!\n");
    sighandler(SIGINT);
  }
  else{
    socket_fd=server_setup();
    printf("Connection Successful! \n");
    printf("Connection Successful! \n");
    printf("Entering preparatory phase!\n");
    setup(user_board, attack_board);
    while(1){
      if(game(user_board, attack_board, socket_fd, 0)) {
        break;
      }
    }
    printf("Thank you for playing!\n");
    sighandler(SIGINT);
  }
}
