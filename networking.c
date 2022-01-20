#include "networking.h"

int server_setup() {
  //use getaddrinfo
  struct addrinfo * hints, * results;
  struct ifaddrs * addrs, * tmp;
  char ipstr[INET6_ADDRSTRLEN];
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server
  getaddrinfo(NULL, "9845", hints, &results);  //Server sets node to NULL

  getifaddrs(&addrs);
  tmp = addrs;

  while (tmp)
  {
    if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
    {
        struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
        printf("%s: %s\n", tmp->ifa_name, inet_ntoa(pAddr->sin_addr));
    }

    tmp = tmp->ifa_next;
  }

  freeifaddrs(addrs);

  //create socket
  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  bind(sd, results->ai_addr, results->ai_addrlen);

  listen(sd, 10);

  int client_socket;
  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  printf("[Server] Waiting for connection...\n");
  client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);
  printf("[Server] Connection made!\n");
  free(hints);
  freeaddrinfo(results);
  return client_socket;
}

int client_setup() {
  //use getaddrinfo
  char s[50];
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  printf("Enter IP address of desired game: ");
  fgets(s, 50, stdin);
  s[strcspn(s, "\n")] = 0;
  getaddrinfo(s, "9845", hints, &results);  //Server sets node to NULL

  //create socket
  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  printf("[Client] Waiting for connection...\n");
  connect(sd, results->ai_addr, results->ai_addrlen);
  printf("[Client] Connection made!\n");
  free(hints);
  freeaddrinfo(results);
  return sd;
}
