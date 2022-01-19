//Preliminary game setup, still needs work, will incorporate into other file(s)
//later.


#include "pipe_networking.h"

int carrier(int board[10][10]);
int battleship(int board[10][10], int coords[4][2]);
int cruiser(int board[10][10], int coords[3][2]);
int sub(int board[10][10], int coords[3][2]);
int destroyer(int board[10][10], int coords[2][2]);
int error_check(int x, int y, int board[10][10]);
int letter_to_num(char letter);

int main() {
  int i, j;
  int user_board[10][10];
  int attack_board[10][10];
  int battle[4][2];
  int carr_sub[3][2];
  int dest[2][2];

  carrier(user_board);
  battleship(user_board, battle);
  cruiser(user_board, carr_sub);
  sub(user_board, carr_sub);
  destroyer(user_board, dest);

  printf("\nYour attack board:\n");
  for(j = 0; j < 10; j++) {
    for(i = 0; i < 10; i++) {
      attack_board[i][j] = 0;
      printf("%d ", attack_board[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int carrier(int board[10][10]) {
  printf("Your board:\n");
  //Sets the board up.
  //Also ensures that, if the user inputs invalid coordinates, the board is
  //reset.
  int i, j;
  for(j = 0; j < 10; j++) {
    for(i = 0; i < 10; i++) {
      board[i][j] = 0;
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  printf("\nState where you will like to place your carrier.\n");
  printf("Type the coordinates in this manner: (Letter)(Number) \n");
  printf("Note: The lowest letter is A and the highest is J. The lowest number is 1 and the highest is 10.\n");

  char letter;
  int x;
  int y;
  while(1) {
    scanf("%c %d", &letter, &y);
    y -= 1;
    x = letter_to_num(letter);

    if(error_check(x, y, board) == -1) {
      printf("\nERROR: Enter valid coordinates.\n\n");
      continue;
    }
    break;
  }
  board[x][y] = 1;

  printf("\nWould you like your ship oriented horizontally? ");
  printf("(Answering \"no\" to this question will orient it vertically.) ");

  int check;

  //Makes sure that, unless the user inputs valid coordinates for the front of
  //the ship, the program will continually prompt them for coordinates.
  while(1) {
    char s[10];
    fgets(s, 10, stdin);
    s[strcspn(s, "\n")] = '\0';

    if(strcmp(s, "no") == 0 || strcmp(s, "No") == 0 || strcmp(s, "n") == 0 || strcmp(s, "N") == 0) {
      printf("Would you like to place the ship facing up or down? ");

      while(1) {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';
        if(strcmp(s, "Up") == 0 || strcmp(s, "up") == 0 || strcmp(s, "u") == 0) {
          for(i = 1; i < 5; i++) {
            check = error_check(x, y-i, board);
            if(check == -1) {
              break;
            }

            board[x][y-i] = 1;
          }
          break;
        }
        else if(strcmp(s, "Down") == 0 || strcmp(s, "down") == 0 || strcmp(s, "d") == 0) {
          for(i = 1; i < 5; i++) {
            check = error_check(x, y+i, board);
            if(check == -1) {
              break;
            }

            board[x][y+i] = 1;
          }
          break;
        }
        else {
          printf("Please enter \"up\" or \"down\": ");
        }
      }
      break;
    }

    else if(strcmp(s, "yes") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "y") == 0 || strcmp(s, "Y") == 0) {
      printf("Would you like to place the ship facing left or right? ");

      while(1) {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';

        if(strcmp(s, "Left") == 0 || strcmp(s, "left") == 0 || strcmp(s, "l") == 0) {
          for(i = 1; i < 5; i++) {
            check = error_check(x-i, y, board);
            if(check == -1) {
              break;
            }

            board[x-i][y] = 1;
          }
          break;
        }
        else if(strcmp(s, "Right") == 0 || strcmp(s, "right") == 0 || strcmp(s, "r") == 0) {
          for(i = 1; i < 5; i++) {
            check = error_check(x+i, y, board);
            if(check == -1) {
              break;
            }

            board[x+i][y];
          }
          break;
        }
        else {
          printf("Please enter \"left\" or \"right\": ");
        }
      }
      break;
    }
    else {
      printf("Please enter \"yes\" or \"no\": ");
    }
  }

  if(check == -1) {
    printf("\nERROR: Please input new coordinates.\n");
    carrier(board);
    return 0;
  }

  printf("\nYour board:\n");
  for(j = 0; j < 10; j++) {
    for(i = 0; i < 10; i++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int battleship(int board[10][10], int coords[4][2]) {

  printf("\nState where you will like to place your battleship.\n");

  int i, j;
  for(i = 0; i < 4; i++) {
    coords[i][0] = 0;
    coords[i][1] = 0;
  }

  //A separate array is necessary because the board cannot reset after the user
  //inputs invalid coordinates at this point, as that would be annoying. Instead,
  //this array stores the coordinates beforehand and the program checks to see if
  //they are valid before putting them on the board.
  char letter;
  int x;
  int y;
  while(1) {
    scanf("%c %d", &letter, &y);
    y -= 1;
    x = letter_to_num(letter);

    if(error_check(x, y, board) == -1) {
      printf("\nERROR: Enter valid coordinates.\n\n");
      continue;
    }

    coords[0][0] = x;
    coords[0][1] = y;
    break;
  }

  printf("\nWould you like your ship oriented horizontally? ");
  printf("(Answering \"no\" to this question will orient it vertically.) ");

  int check;

  //Makes sure that, unless the user inputs valid coordinates for the front of
  //the ship, the program will continually prompt them for coordinates.
  while(1) {
    char s[10];
    fgets(s, 10, stdin);
    s[strcspn(s, "\n")] = '\0';

    if(strcmp(s, "no") == 0 || strcmp(s, "No") == 0 || strcmp(s, "n") == 0 || strcmp(s, "N") == 0) {
      printf("Would you like to place the ship facing up or down? ");

      while(1) {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';
        if(strcmp(s, "Up") == 0 || strcmp(s, "up") == 0 || strcmp(s, "u") == 0) {
          for(i = 1; i < 4; i++) {
            check = error_check(x, y-i, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y-i;
          }
          break;
        }
        else if(strcmp(s, "Down") == 0 || strcmp(s, "down") == 0 || strcmp(s, "d") == 0) {
          for(i = 1; i < 4; i++) {
            check = error_check(x, y+i, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y+i;
          }
          break;
        }
        else {
          printf("Please enter \"up\" or \"down\": ");
        }
      }
      break;
    }

    else if(strcmp(s, "yes") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "y") == 0 || strcmp(s, "Y") == 0) {
      printf("Would you like to place the ship facing left or right? ");

      while(1) {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';

        if(strcmp(s, "Left") == 0 || strcmp(s, "left") == 0 || strcmp(s, "l") == 0) {
          for(i = 1; i < 4; i++) {
            check = error_check(x-i, y, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x-i;
            coords[i][1] = y;
          }
          break;
        }
        else if(strcmp(s, "Right") == 0 || strcmp(s, "right") == 0 || strcmp(s, "r") == 0) {
          for(i = 1; i < 4; i++) {
            check = error_check(x+i, y, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x+i;
            coords[i][1] = y;
          }
          break;
        }
        else {
          printf("Please enter \"left\" or \"right\": ");
        }
      }
      break;
    }
    else {
      printf("Please enter \"yes\" or \"no\": ");
    }
  }

  if(check == -1) {
    printf("\nERROR: Please input new coordinates.\n");
    battleship(board, coords);

    return 0;
  }

  for(i = 0; i < 4; i++) {
    board[coords[i][0]][coords[i][1]] = 2;
  }

  printf("\nYour board:\n");
  for(j = 0; j < 10; j++) {
    for(i = 0; i < 10; i++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int cruiser(int board[10][10], int coords[3][2]) {

  printf("\nState where you will like to place your cruiser.\n");

  //A separate array is necessary because the board cannot reset after the user
  //inputs invalid coordinates at this point, as that would be annoying. Instead,
  //this array stores the coordinates beforehand and the program checks to see if
  //they are valid before putting them on the board.
  int i, j;
  for(i = 0; i < 3; i++) {
    coords[i][0] = 0;
    coords[i][1] = 0;
  }

  char letter;
  int x;
  int y;
  while(1) {
    scanf("%c %d", &letter, &y);
    y -= 1;
    x = letter_to_num(letter);

    if(error_check(x, y, board) == -1) {
      printf("\nERROR: Enter valid coordinates.\n\n");
      continue;
    }

    coords[0][0] = x;
    coords[0][1] = y;
    break;
  }

  printf("\nWould you like your ship oriented horizontally? ");
  printf("(Answering \"no\" to this question will orient it vertically.) ");

  int check;

  //Makes sure that, unless the user inputs valid coordinates for the front of
  //the ship, the program will continually prompt them for coordinates.
  while(1) {
    char s[10];
    fgets(s, 10, stdin);
    s[strcspn(s, "\n")] = '\0';

    if(strcmp(s, "no") == 0 || strcmp(s, "No") == 0 || strcmp(s, "n") == 0 || strcmp(s, "N") == 0) {
      printf("Would you like to place the ship facing up or down? ");

      while(1) {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';
        if(strcmp(s, "Up") == 0 || strcmp(s, "up") == 0 || strcmp(s, "u") == 0) {
          for(i = 1; i < 3; i++) {
            check = error_check(x, y-i, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y-i;
          }
          break;
        }
        else if(strcmp(s, "Down") == 0 || strcmp(s, "down") == 0 || strcmp(s, "d") == 0) {
          for(i = 1; i < 3; i++) {
            check = error_check(x, y+i, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y+i;
          }
          break;
        }
        else {
          printf("Please enter \"up\" or \"down\": ");
        }
      }
      break;
    }

    else if(strcmp(s, "yes") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "y") == 0 || strcmp(s, "Y") == 0) {
      printf("Would you like to place the ship facing left or right? ");

      while(1) {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';

        if(strcmp(s, "Left") == 0 || strcmp(s, "left") == 0 || strcmp(s, "l") == 0) {
          for(i = 1; i < 3; i++) {
            check = error_check(x-i, y, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x-i;
            coords[i][1] = y;
          }
          break;
        }
        else if(strcmp(s, "Right") == 0 || strcmp(s, "right") == 0 || strcmp(s, "r") == 0) {
          for(i = 1; i < 3; i++) {
            check = error_check(x+i, y, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x+i;
            coords[i][1] = y;
          }
          break;
        }
        else {
          printf("Please enter \"left\" or \"right\": ");
        }
      }
      break;
    }
    else {
      printf("Please enter \"yes\" or \"no\": ");
    }
  }

  if(check == -1) {
    printf("\nERROR: Please input new coordinates.\n");
    cruiser(board, coords);
    return 0;
  }

  for(i = 0; i < 3; i++) {
    board[coords[i][0]][coords[i][1]] = 3;
  }

  printf("\nYour board:\n");
  for(j = 0; j < 10; j++) {
    for(i = 0; i < 10; i++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int sub(int board[10][10], int coords[3][2]) {

  printf("\nState where you will like to place your submarine.\n");

  //A separate array is necessary because the board cannot reset after the user
  //inputs invalid coordinates at this point, as that would be annoying. Instead,
  //this array stores the coordinates beforehand and the program checks to see if
  //they are valid before putting them on the board.
  int i, j;
  for(i = 0; i < 3; i++) {
    coords[i][0] = 0;
    coords[i][1] = 0;
  }

  char letter;
  int x;
  int y;
  while(1) {
    scanf("%c %d", &letter, &y);
    y -= 1;
    x = letter_to_num(letter);

    if(error_check(x, y, board) == -1) {
      printf("\nERROR: Enter valid coordinates.\n\n");
      continue;
    }

    coords[0][0] = x;
    coords[0][1] = y;
    break;
  }

  printf("\nWould you like your ship oriented horizontally? ");
  printf("(Answering \"no\" to this question will orient it vertically.) ");

  int check;

  //Makes sure that, unless the user inputs valid coordinates for the front of
  //the ship, the program will continually prompt them for coordinates.
  while(1) {
    char s[10];
    fgets(s, 10, stdin);
    s[strcspn(s, "\n")] = '\0';

    if(strcmp(s, "no") == 0 || strcmp(s, "No") == 0 || strcmp(s, "n") == 0 || strcmp(s, "N") == 0) {
      printf("Would you like to place the ship facing up or down? ");

      while(1) {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';
        if(strcmp(s, "Up") == 0 || strcmp(s, "up") == 0 || strcmp(s, "u") == 0) {
          for(i = 1; i < 3; i++) {
            check = error_check(x, y-i, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y-i;
          }
          break;
        }
        else if(strcmp(s, "Down") == 0 || strcmp(s, "down") == 0 || strcmp(s, "d") == 0) {
          for(i = 1; i < 3; i++) {
            check = error_check(x, y+i, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y+i;
          }
          break;
        }
        else {
          printf("Please enter \"up\" or \"down\": ");
        }
      }
      break;
    }

    else if(strcmp(s, "yes") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "y") == 0 || strcmp(s, "Y") == 0) {
      printf("Would you like to place the ship facing left or right? ");

      while(1) {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';

        if(strcmp(s, "Left") == 0 || strcmp(s, "left") == 0 || strcmp(s, "l") == 0) {
          for(i = 1; i < 3; i++) {
            check = error_check(x-i, y, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x-i;
            coords[i][1] = y;
          }
          break;
        }
        else if(strcmp(s, "Right") == 0 || strcmp(s, "right") == 0 || strcmp(s, "r") == 0) {
          for(i = 1; i < 3; i++) {
            check = error_check(x+i, y, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x+i;
            coords[i][1] = y;
          }
          break;
        }
        else {
          printf("Please enter \"left\" or \"right\": ");
        }
      }
      break;
    }
    else {
      printf("Please enter \"yes\" or \"no\": ");
    }
  }

  if(check == -1) {
    printf("\nERROR: Please input new coordinates.\n");
    sub(board, coords);
    return 0;
  }

  for(i = 0; i < 3; i++) {
    board[coords[i][0]][coords[i][1]] = 4;
  }

  printf("\nYour board:\n");
  for(j = 0; j < 10; j++) {
    for(i = 0; i < 10; i++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int destroyer(int board[10][10], int coords[2][2]) {

  printf("\nState where you will like to place your destroyer.\n");

  //A separate array is necessary because the board cannot reset after the user
  //inputs invalid coordinates at this point, as that would be annoying. Instead,
  //this array stores the coordinates beforehand and the program checks to see if
  //they are valid before putting them on the board.
  int i, j;
  for(i = 0; i < 2; i++) {
    coords[i][0] = 0;
    coords[i][1] = 0;
  }

  char letter;
  int x;
  int y;
  while(1) {
    scanf("%c %d", &letter, &y);
    y -= 1;
    x = letter_to_num(letter);

    if(error_check(x, y, board) == -1) {
      printf("\nERROR: Enter valid coordinates.\n\n");
      continue;
    }

    coords[0][0] = x;
    coords[0][1] = y;
    break;
  }

  printf("\nWould you like your ship oriented horizontally? ");
  printf("(Answering \"no\" to this question will orient it vertically.) ");

  int check;

  //Makes sure that, unless the user inputs valid coordinates for the front of
  //the ship, the program will continually prompt them for coordinates.
  while(1) {
    char s[10];
    fgets(s, 10, stdin);
    s[strcspn(s, "\n")] = '\0';

    if(strcmp(s, "no") == 0 || strcmp(s, "No") == 0 || strcmp(s, "n") == 0 || strcmp(s, "N") == 0) {
      printf("Would you like to place the ship facing up or down? ");

      while(1) {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';
        if(strcmp(s, "Up") == 0 || strcmp(s, "up") == 0 || strcmp(s, "u") == 0) {
          for(i = 1; i < 2; i++) {
            check = error_check(x, y-i, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y-i;
          }
          break;
        }
        else if(strcmp(s, "Down") == 0 || strcmp(s, "down") == 0 || strcmp(s, "d") == 0) {
          for(i = 1; i < 2; i++) {
            check = error_check(x, y+i, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x;
            coords[i][1] = y+i;
          }
          break;
        }
        else {
          printf("Please enter \"up\" or \"down\": ");
        }
      }
      break;
    }

    else if(strcmp(s, "yes") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "y") == 0 || strcmp(s, "Y") == 0) {
      printf("Would you like to place the ship facing left or right? ");

      while(1) {
        fgets(s, 10, stdin);
        s[strcspn(s, "\n")] = '\0';

        if(strcmp(s, "Left") == 0 || strcmp(s, "left") == 0 || strcmp(s, "l") == 0) {
          for(i = 1; i < 2; i++) {
            check = error_check(x-i, y, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x-i;
            coords[i][1] = y;
          }
          break;
        }
        else if(strcmp(s, "Right") == 0 || strcmp(s, "right") == 0 || strcmp(s, "r") == 0) {
          for(i = 1; i < 2; i++) {
            check = error_check(x+i, y, board);
            if(check == -1) {
              break;
            }

            coords[i][0] = x+i;
            coords[i][1] = y;
          }
          break;
        }
        else {
          printf("Please enter \"left\" or \"right\": ");
        }
      }
      break;
    }
    else {
      printf("Please enter \"yes\" or \"no\": ");
    }
  }

  if(check == -1) {
    printf("\nERROR: Please input new coordinates.\n");
    sub(board, coords);
    return 0;
  }

  for(i = 0; i < 2; i++) {
    board[coords[i][0]][coords[i][1]] = 5;
  }

  printf("\nYour board:\n");
  for(j = 0; j < 10; j++) {
    for(i = 0; i < 10; i++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  return 0;
}

int error_check(int x, int y, int board[10][10]) {
  if(x < 0 || x > 9 || y < 0 || y > 9) {
    return -1;
  }
  if(board[x][y] != 0) {
    return -1;
  }
  return 0;
}

int letter_to_num(char letter) {
  if(letter == 'A' || letter == 'a') {
    return 0;
  }
  else if(letter == 'B' || letter == 'b') {
    return 1;
  }
  else if(letter == 'C' || letter == 'c') {
    return 2;
  }
  else if(letter == 'D' || letter == 'd') {
    return 3;
  }
  else if(letter == 'E' || letter == 'e') {
    return 4;
  }
  else if(letter == 'F' || letter == 'f') {
    return 5;
  }
  else if(letter == 'G' || letter == 'g') {
    return 6;
  }
  else if(letter == 'H' || letter == 'h') {
    return 7;
  }
  else if(letter == 'I' || letter == 'i') {
    return 8;
  }
  else if(letter == 'J' || letter == 'j') {
    return 9;
  }
  else {
    return -1;
  }
}
