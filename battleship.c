#include "SDL_global_variables.h"
#include "networking.h"
#include "setup.h"
#include "game.h"
#include "SDL_setup.h"

#include <SDL2/SDL.h>

static void sighandler(int signo)
{
  if (signo == SIGINT)
  {
    printf("\nPlayer has left, exiting...\n");
    exit(0);
  }
}

int main()
{
  signal(SIGINT, sighandler);
  int user_board[10][10];
  int attack_board[10][10];
  char *a = malloc(10 * sizeof(char *));
  char *s = malloc(50 * sizeof(char *));
  int d = -1;
  int socket_fd;

  printf("Welcome to Battleship v1.0! \nPlease enter whether you want to: \n Create a Game [0] \n Join a Game [1] \n Help [2] \n\n");
  printf("WARNING: The host should NOT ctrl-C until the other player has left. ");
  printf("This will prevent host-client connections in future games. ");
  printf("The game will have to be recompiled to be successfully ran again.\n");
  while (1)
  {
    fgets(a, 10, stdin);
    if (strcmp(a, "0\n") == 0)
    {
      printf("Creating a Game!\n");
      d = 0;
      break;
    }
    else if (strcmp(a, "1\n") == 0)
    {
      printf("Joining a Game!\n");
      d = 1;
      break;
    }
    else if (strcmp(a, "2\n") == 0)
    {
      printf("\nBATTLESHIP\n");
      printf("\nThe objective of the game is to sink all five of your opponent's ships first.\n");
      printf("Before you begin, you'll each have to place these ships on your virtual board.\n");
      printf("\nYou will be prompted to input coordinates in this format: '(Letter)(Number)'\n");
      printf("How ship placements will work is that these coordinates are treated like the \"head\" of the ship.\n");
      printf("Thus, when you are prompted to place each ship either horizontally left or right or vertically up or down, ");
      printf("all the other coordinates will be left, right, up, or down from the one you specify, respectively.\n\n");
      printf("When eveything is set up, you will see numbers on a 10x10 grid. 0 denotes an empty space. 1 denotes your carrier. 2 denotes your battleship. ");
      printf("3 denotes your cruiser. 4 denotes your submarine. 5 denotes your destroyer.\n");
      printf("As you shoot, 6 denotes a successful shot. 7 denotes an unsuccessful shot. You will have a virtual attack board ");
      printf("to keep track of your shots.\n\n");
      printf("Good luck and godspeed, admiral.\n");
    }
    else
    {
      printf("Invalid response, please try again: \n ");
    }
  }

  printf("before SDL_setup \n");

  //setting up SDL and game window
  struct WindowInfo info;
  info = SDL_setup();

  if (d)
  {
    socket_fd = client_setup();
    printf("Connection Successful! \n");
    printf("Entering preparatory phase!\n");
    setup(user_board, attack_board, info);
    while (1)
    {
      if (game(user_board, attack_board, socket_fd, 1))
      {
        break;
      }
    }
    printf("Thank you for playing!\n");
    //sighandler(SIGINT);
  }
  else
  {
    socket_fd = server_setup();
    printf("Connection Successful! \n");
    printf("Connection Successful! \n");
    printf("Entering preparatory phase!\n");
    setup(user_board, attack_board, info);
    while (1)
    {
      if (game(user_board, attack_board, socket_fd, 0))
      {
        break;
      }
    }
    printf("Thank you for playing!\n");
    //sighandler(SIGINT);
  }

  free(a);
  free(s);

  close(socket_fd);

  //cleaning sdl
  SDL_DestroyRenderer(info.renderer);
  SDL_DestroyWindow(info.window);
  SDL_Quit();
  return 0;
}
