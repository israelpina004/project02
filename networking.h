#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>

int server_setup();
int client_setup();
