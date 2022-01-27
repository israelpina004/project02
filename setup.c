//Preliminary game setup, still needs work, will incorporate into other file(s)
//later.
#include "networking.h"
#include "setup.h"

#include "SDL_functions.h"

int setup(int user_board[10][10], int attack_board[10][10], struct WindowInfo info)
{
  int i, j;
  int battle[4][2];
  int carr_sub[3][2];
  int dest[2][2];

  carrier(user_board, info);
  battleship(user_board, battle, info);
  cruiser(user_board, carr_sub, info);
  sub(user_board, carr_sub, info);
  destroyer(user_board, dest, info);

  for (j = 0; j < 10; j++)
  {
    for (i = 0; i < 10; i++)
    {
      attack_board[i][j] = 0;
    }
  }

  return 0;
}

int carrier(int board[10][10], struct WindowInfo info)
{
  printf("Your board:\n");
  //Sets the board up.
  //Also ensures that, if the user inputs invalid coordinates, the board is
  //reset.
  int i, j;
  for (j = 0; j < 10; j++)
  {
    for (i = 0; i < 10; i++)
    {
      board[i][j] = 0;
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  printf("\nState where you will like to place your carrier. Press S when you are satisfied with your location\n");

  struct Coords cruise_coords = render_ship(info, 5, board);

  // printf("Type the coordinates in this manner: (Letter)(Number) \n");
  // printf("Note: The lowest letter is A and the highest is J. The lowest number is 1 and the highest is 10.\n");

  char letter;
  int x = cruise_coords.x;
  int y = cruise_coords.y;
  // while (1)
  // {
  //   scanf("%c %d", &letter, &y);
  //   y -= 1;
  //   x = letter_to_num(letter);

  //   if (error_check(x, y, board) == -1)
  //   {
  //     printf("\nERROR: Enter valid coordinates.\n\n");
  //     continue;
  //   }
  //   break;
  // }

  board[x][y] = 1;

  printf("\nWould you like your ship oriented horizontally? ");
  printf("(Answering \"no\" to this question will orient it vertically.) ");

  int check;

  //Makes sure that, unless the user inputs valid coordinates for the front of
  //the ship, the program will continually prompt them for coordinates.
  while (1)
  {
    char s[10];
    fgets(s, 10, stdin);
    s[strcspn(s, "\n")] = '\0';

    if (strcmp(s, "no") == 0 || strcmp(s, "No") == 0 || strcmp(s, "n") == 0 || strcmp(s, "N") == 0)
    {
      printf("Would you like to place the ship facing up or down? ");

      while (1)
      {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';
        if (strcmp(s, "Up") == 0 || strcmp(s, "up") == 0 || strcmp(s, "u") == 0)
        {
          for (i = 1; i < 5; i++)
          {
            check = error_check(x, y - i, board);
            if (check == -1)
            {
              break;
            }

            board[x][y - i] = 1;
          }
          break;
        }
        else if (strcmp(s, "Down") == 0 || strcmp(s, "down") == 0 || strcmp(s, "d") == 0)
        {
          for (i = 1; i < 5; i++)
          {
            check = error_check(x, y + i, board);
            if (check == -1)
            {
              break;
            }

            board[x][y + i] = 1;
          }
          break;
        }
        else
        {
          printf("Please enter \"up\" or \"down\": ");
        }
      }
      break;
    }

    else if (strcmp(s, "yes") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "y") == 0 || strcmp(s, "Y") == 0)
    {
      printf("Would you like to place the ship facing left or right? ");

      while (1)
      {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';

        if (strcmp(s, "Left") == 0 || strcmp(s, "left") == 0 || strcmp(s, "l") == 0)
        {
          for (i = 1; i < 5; i++)
          {
            check = error_check(x - i, y, board);
            if (check == -1)
            {
              break;
            }

            board[x - i][y] = 1;
          }
          break;
        }
        else if (strcmp(s, "Right") == 0 || strcmp(s, "right") == 0 || strcmp(s, "r") == 0)
        {
          for (i = 1; i < 5; i++)
          {
            check = error_check(x + i, y, board);
            if (check == -1)
            {
              break;
            }

            board[x + i][y] = 1;
          }
          break;
        }
        else
        {
          printf("Please enter \"left\" or \"right\": ");
        }
      }
      break;
    }
    else
    {
      printf("Please enter \"yes\" or \"no\": ");
    }
  }

  if (check == -1)
  {
    printf("\nERROR: Please input new coordinates.\n");
    carrier(board, info);
    return 0;
  }

  printf("\nYour board:\n");
  for (j = 0; j < 10; j++)
  {
    for (i = 0; i < 10; i++)
    {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int battleship(int board[10][10], int coords[4][2], struct WindowInfo info)
{

  printf("\nState where you will like to place your battleship.\n");

  struct Coords battleship_coords = render_ship(info, 4, board);

  int i,
      j;

  for (i = 0; i < 4; i++)
  {
    coords[i][0] = 0;
    coords[i][1] = 0;
  }

  //A separate array is necessary because the board cannot reset after the user
  //inputs invalid coordinates at this point, as that would be annoying. Instead,
  //this array stores the coordinates beforehand and the program checks to see if
  //they are valid before putting them on the board.
  char letter;
  int x = battleship_coords.x;
  int y = battleship_coords.y;
  coords[0][0] = x;
  coords[0][1] = y;

  // while (1)
  // {
  //   scanf("%c %d", &letter, &y);
  //   y -= 1;
  //   x = letter_to_num(letter);

  //   if (error_check(x, y, board) == -1)
  //   {
  //     printf("\nERROR: Enter valid coordinates.\n\n");
  //     continue;
  //   }

  //   break;
  // }

  printf("\nWould you like your ship oriented horizontally? ");
  printf("(Answering \"no\" to this question will orient it vertically.) ");

  int check;

  //Makes sure that, unless the user inputs valid coordinates for the front of
  //the ship, the program will continually prompt them for coordinates.
  while (1)
  {
    char s[10];
    fgets(s, 10, stdin);
    s[strcspn(s, "\n")] = '\0';

    if (strcmp(s, "no") == 0 || strcmp(s, "No") == 0 || strcmp(s, "n") == 0 || strcmp(s, "N") == 0)
    {
      printf("Would you like to place the ship facing up or down? ");

      while (1)
      {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';
        if (strcmp(s, "Up") == 0 || strcmp(s, "up") == 0 || strcmp(s, "u") == 0)
        {
          for (i = 1; i < 4; i++)
          {
            check = error_check(x, y - i, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y - i;
          }
          break;
        }
        else if (strcmp(s, "Down") == 0 || strcmp(s, "down") == 0 || strcmp(s, "d") == 0)
        {
          for (i = 1; i < 4; i++)
          {
            check = error_check(x, y + i, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y + i;
          }
          break;
        }
        else
        {
          printf("Please enter \"up\" or \"down\": ");
        }
      }
      break;
    }

    else if (strcmp(s, "yes") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "y") == 0 || strcmp(s, "Y") == 0)
    {
      printf("Would you like to place the ship facing left or right? ");

      while (1)
      {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';

        if (strcmp(s, "Left") == 0 || strcmp(s, "left") == 0 || strcmp(s, "l") == 0)
        {
          for (i = 1; i < 4; i++)
          {
            check = error_check(x - i, y, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x - i;
            coords[i][1] = y;
          }
          break;
        }
        else if (strcmp(s, "Right") == 0 || strcmp(s, "right") == 0 || strcmp(s, "r") == 0)
        {
          for (i = 1; i < 4; i++)
          {
            check = error_check(x + i, y, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x + i;
            coords[i][1] = y;
          }
          break;
        }
        else
        {
          printf("Please enter \"left\" or \"right\": ");
        }
      }
      break;
    }
    else
    {
      printf("Please enter \"yes\" or \"no\": ");
    }
  }

  if (check == -1)
  {
    printf("\nERROR: Please input new coordinates.\n");
    battleship(board, coords, info);

    return 0;
  }

  for (i = 0; i < 4; i++)
  {
    board[coords[i][0]][coords[i][1]] = 2;
  }

  printf("\nYour board:\n");
  for (j = 0; j < 10; j++)
  {
    for (i = 0; i < 10; i++)
    {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int cruiser(int board[10][10], int coords[3][2], struct WindowInfo info)
{

  printf("\nState where you will like to place your cruiser.\n");

  //A separate array is necessary because the board cannot reset after the user
  //inputs invalid coordinates at this point, as that would be annoying. Instead,
  //this array stores the coordinates beforehand and the program checks to see if
  //they are valid before putting them on the board.

  struct Coords cruiser_coords = render_ship(info, 3, board);

  int i, j;
  for (i = 0; i < 3; i++)
  {
    coords[i][0] = 0;
    coords[i][1] = 0;
  }

  char letter;
  int x = cruiser_coords.x;
  int y = cruiser_coords.y;
  coords[0][0] = x;
  coords[0][1] = y;
  // while (1)
  // {
  //   scanf("%c %d", &letter, &y);
  //   y -= 1;
  //   x = letter_to_num(letter);

  //   if (error_check(x, y, board) == -1)
  //   {
  //     printf("\nERROR: Enter valid coordinates.\n\n");
  //     continue;
  //   }

  //   break;
  // }

  printf("\nWould you like your ship oriented horizontally? ");
  printf("(Answering \"no\" to this question will orient it vertically.) ");

  int check;

  //Makes sure that, unless the user inputs valid coordinates for the front of
  //the ship, the program will continually prompt them for coordinates.
  while (1)
  {
    char s[10];
    fgets(s, 10, stdin);
    s[strcspn(s, "\n")] = '\0';

    if (strcmp(s, "no") == 0 || strcmp(s, "No") == 0 || strcmp(s, "n") == 0 || strcmp(s, "N") == 0)
    {
      printf("Would you like to place the ship facing up or down? ");

      while (1)
      {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';
        if (strcmp(s, "Up") == 0 || strcmp(s, "up") == 0 || strcmp(s, "u") == 0)
        {
          for (i = 1; i < 3; i++)
          {
            check = error_check(x, y - i, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y - i;
          }
          break;
        }
        else if (strcmp(s, "Down") == 0 || strcmp(s, "down") == 0 || strcmp(s, "d") == 0)
        {
          for (i = 1; i < 3; i++)
          {
            check = error_check(x, y + i, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y + i;
          }
          break;
        }
        else
        {
          printf("Please enter \"up\" or \"down\": ");
        }
      }
      break;
    }

    else if (strcmp(s, "yes") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "y") == 0 || strcmp(s, "Y") == 0)
    {
      printf("Would you like to place the ship facing left or right? ");

      while (1)
      {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';

        if (strcmp(s, "Left") == 0 || strcmp(s, "left") == 0 || strcmp(s, "l") == 0)
        {
          for (i = 1; i < 3; i++)
          {
            check = error_check(x - i, y, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x - i;
            coords[i][1] = y;
          }
          break;
        }
        else if (strcmp(s, "Right") == 0 || strcmp(s, "right") == 0 || strcmp(s, "r") == 0)
        {
          for (i = 1; i < 3; i++)
          {
            check = error_check(x + i, y, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x + i;
            coords[i][1] = y;
          }
          break;
        }
        else
        {
          printf("Please enter \"left\" or \"right\": ");
        }
      }
      break;
    }
    else
    {
      printf("Please enter \"yes\" or \"no\": ");
    }
  }

  if (check == -1)
  {
    printf("\nERROR: Please input new coordinates.\n");
    cruiser(board, coords, info);
    return 0;
  }

  for (i = 0; i < 3; i++)
  {
    board[coords[i][0]][coords[i][1]] = 3;
  }

  printf("\nYour board:\n");
  for (j = 0; j < 10; j++)
  {
    for (i = 0; i < 10; i++)
    {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int sub(int board[10][10], int coords[3][2], struct WindowInfo info)
{

  struct Coords sub_coords = render_ship(info, 3, board);

  printf("\nState where you will like to place your submarine.\n");

  //A separate array is necessary because the board cannot reset after the user
  //inputs invalid coordinates at this point, as that would be annoying. Instead,
  //this array stores the coordinates beforehand and the program checks to see if
  //they are valid before putting them on the board.
  int i, j;
  for (i = 0; i < 3; i++)
  {
    coords[i][0] = 0;
    coords[i][1] = 0;
  }

  char letter;
  int x = sub_coords.x;
  int y = sub_coords.y;
  coords[0][0] = x;
  coords[0][1] = y;

  // while (1)
  // {
  //   scanf("%c %d", &letter, &y);
  //   y -= 1;
  //   x = letter_to_num(letter);

  //   if (error_check(x, y, board) == -1)
  //   {
  //     printf("\nERROR: Enter valid coordinates.\n\n");
  //     continue;
  //   }

  //   break;
  // }

  printf("\nWould you like your ship oriented horizontally? ");
  printf("(Answering \"no\" to this question will orient it vertically.) ");

  int check;

  //Makes sure that, unless the user inputs valid coordinates for the front of
  //the ship, the program will continually prompt them for coordinates.
  while (1)
  {
    char s[10];
    fgets(s, 10, stdin);
    s[strcspn(s, "\n")] = '\0';

    if (strcmp(s, "no") == 0 || strcmp(s, "No") == 0 || strcmp(s, "n") == 0 || strcmp(s, "N") == 0)
    {
      printf("Would you like to place the ship facing up or down? ");

      while (1)
      {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';
        if (strcmp(s, "Up") == 0 || strcmp(s, "up") == 0 || strcmp(s, "u") == 0)
        {
          for (i = 1; i < 3; i++)
          {
            check = error_check(x, y - i, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y - i;
          }
          break;
        }
        else if (strcmp(s, "Down") == 0 || strcmp(s, "down") == 0 || strcmp(s, "d") == 0)
        {
          for (i = 1; i < 3; i++)
          {
            check = error_check(x, y + i, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y + i;
          }
          break;
        }
        else
        {
          printf("Please enter \"up\" or \"down\": ");
        }
      }
      break;
    }

    else if (strcmp(s, "yes") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "y") == 0 || strcmp(s, "Y") == 0)
    {
      printf("Would you like to place the ship facing left or right? ");

      while (1)
      {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';

        if (strcmp(s, "Left") == 0 || strcmp(s, "left") == 0 || strcmp(s, "l") == 0)
        {
          for (i = 1; i < 3; i++)
          {
            check = error_check(x - i, y, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x - i;
            coords[i][1] = y;
          }
          break;
        }
        else if (strcmp(s, "Right") == 0 || strcmp(s, "right") == 0 || strcmp(s, "r") == 0)
        {
          for (i = 1; i < 3; i++)
          {
            check = error_check(x + i, y, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x + i;
            coords[i][1] = y;
          }
          break;
        }
        else
        {
          printf("Please enter \"left\" or \"right\": ");
        }
      }
      break;
    }
    else
    {
      printf("Please enter \"yes\" or \"no\": ");
    }
  }

  if (check == -1)
  {
    printf("\nERROR: Please input new coordinates.\n");
    sub(board, coords, info);
    return 0;
  }

  for (i = 0; i < 3; i++)
  {
    board[coords[i][0]][coords[i][1]] = 4;
  }

  printf("\nYour board:\n");
  for (j = 0; j < 10; j++)
  {
    for (i = 0; i < 10; i++)
    {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int destroyer(int board[10][10], int coords[2][2], struct WindowInfo info)
{

  printf("\nState where you will like to place your destroyer.\n");

  //A separate array is necessary because the board cannot reset after the user
  //inputs invalid coordinates at this point, as that would be annoying. Instead,
  //this array stores the coordinates beforehand and the program checks to see if
  //they are valid before putting them on the board.
  int i, j;
  for (i = 0; i < 2; i++)
  {
    coords[i][0] = 0;
    coords[i][1] = 0;
  }

  struct Coords destroyer_coords = render_ship(info, 2, board);

  char letter;
  int x = destroyer_coords.x;
  int y = destroyer_coords.y;

  coords[0][0] = x;
  coords[0][1] = y;

  // while (1)
  // {
  //   scanf("%c %d", &letter, &y);
  //   y -= 1;
  //   x = letter_to_num(letter);

  //   if (error_check(x, y, board) == -1)
  //   {
  //     printf("\nERROR: Enter valid coordinates.\n\n");
  //     continue;
  //   }

  //   break;
  // }

  printf("\nWould you like your ship oriented horizontally? ");
  printf("(Answering \"no\" to this question will orient it vertically.) ");

  int check;

  //Makes sure that, unless the user inputs valid coordinates for the front of
  //the ship, the program will continually prompt them for coordinates.
  while (1)
  {
    char s[10];
    fgets(s, 10, stdin);
    s[strcspn(s, "\n")] = '\0';

    if (strcmp(s, "no") == 0 || strcmp(s, "No") == 0 || strcmp(s, "n") == 0 || strcmp(s, "N") == 0)
    {
      printf("Would you like to place the ship facing up or down? ");

      while (1)
      {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';
        if (strcmp(s, "Up") == 0 || strcmp(s, "up") == 0 || strcmp(s, "u") == 0)
        {
          for (i = 1; i < 2; i++)
          {
            check = error_check(x, y - i, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y - i;
          }
          break;
        }
        else if (strcmp(s, "Down") == 0 || strcmp(s, "down") == 0 || strcmp(s, "d") == 0)
        {
          for (i = 1; i < 2; i++)
          {
            check = error_check(x, y + i, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y + i;
          }
          break;
        }
        else
        {
          printf("Please enter \"up\" or \"down\": ");
        }
      }
      break;
    }

    else if (strcmp(s, "yes") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "y") == 0 || strcmp(s, "Y") == 0)
    {
      printf("Would you like to place the ship facing left or right? ");

      while (1)
      {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';

        if (strcmp(s, "Left") == 0 || strcmp(s, "left") == 0 || strcmp(s, "l") == 0)
        {
          for (i = 1; i < 2; i++)
          {
            check = error_check(x - i, y, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x - i;
            coords[i][1] = y;
          }
          break;
        }
        else if (strcmp(s, "Right") == 0 || strcmp(s, "right") == 0 || strcmp(s, "r") == 0)
        {
          for (i = 1; i < 2; i++)
          {
            check = error_check(x + i, y, board);
            if (check == -1)
            {
              break;
            }

            coords[i][0] = x + i;
            coords[i][1] = y;
          }
          break;
        }
        else
        {
          printf("Please enter \"left\" or \"right\": ");
        }
      }
      break;
    }
    else
    {
      printf("Please enter \"yes\" or \"no\": ");
    }
  }

  if (check == -1)
  {
    printf("\nERROR: Please input new coordinates.\n");
    sub(board, coords, info);
    return 0;
  }

  for (i = 0; i < 2; i++)
  {
    board[coords[i][0]][coords[i][1]] = 5;
  }

  printf("\nYour board:\n");
  for (j = 0; j < 10; j++)
  {
    for (i = 0; i < 10; i++)
    {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int error_check(int x, int y, int board[10][10])
{
  if (x < 0 || x > 9 || y < 0 || y > 9)
  {
    return -1;
  }
  if (board[x][y] != 0)
  {
    return -1;
  }
  return 0;
}

int letter_to_num(char letter)
{
  if (isalpha(letter))
  {
    if (isupper(letter))
    {
      return letter - 65;
    }
    else
    {
      return letter - 97;
    }
  }
  else if (isdigit(letter))
  {
    return letter - '0';
  }
  else
  {
    return -1;
  }
}
