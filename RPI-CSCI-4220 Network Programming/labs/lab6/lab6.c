#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {

  char * hostname = argv[1];
  if (!hostname) {
    printf("Remember to give an arguement!\n");
    exit(1);
  }
  int status;
  struct addrinfo hints;
  struct addrinfo *servinfo, *current;
  struct sockaddr_in *h;


  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((status = getaddrinfo(hostname, "http", &hints, &servinfo)) !=0) {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
      return 1;
  } else {

    for(current = servinfo; current != NULL; current = current->ai_next) {

      struct sockaddr_in *addr;
      addr = (struct sockaddr_in *) current->ai_addr; 
      char buff[100];
      printf("IP Address: %s\n",inet_ntop(current->ai_family,&(addr->sin_addr),&buff,100) );
    }

  }

  freeaddrinfo(servinfo);

}

