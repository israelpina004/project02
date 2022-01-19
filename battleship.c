#include "networking.h"

char* cap(char* s, int size){
  int h;
  for(int i=0;i<size;i++){
    h=s[i];
    if(isalpha(s[i])){
      if(h>96){h=h-32;}else{h=h+32;}
    }
    s[i]=h;
  }
  return s;
}

static void sighandler(int signo){
  if(signo == SIGINT ){
    printf("\nPlayer has left, exiting...\n");
    exit(0);
  }
}

int main(int argc, int argv[]){
  signal(SIGINT, sighandler);
  char a[10];
  char s[50];
  int d=-1;
  int socket_fd;
  printf("Welcome to Battleship v.0.1! \nPlease enter whether you want to: \n Create a Game [0] \n Join a Game [1] \n ");
  while(1){
    fgets(a, 10 ,stdin);
    if(strcmp(a,"0\n")==0){printf("Creating a Game!\n"); d=0; break;}
    else if(strcmp(a,"1\n")==0){printf("Joining a Game!\n"); d=1; break;}
    else{printf("Invalid response, please try again: \n ");}
  }
  if(d){
    socket_fd=client_setup();
    printf("Chat initiated! \n");
    while(1){
      fgets(s, 50, stdin);
      write(socket_fd, s, sizeof(s));
      read(socket_fd, s, sizeof(s));
      printf("%s\n",s);
    }
  }else{
    socket_fd=server_setup();
    printf("Chat initiated! \n");
    while(1){
      if(read(socket_fd, s, sizeof(s))<=0){break;}
      printf("%s\n",s);
      fgets(s, 50, stdin);
      write(socket_fd, s, sizeof(s));
    }
    sighandler(SIGINT);
  }
}
