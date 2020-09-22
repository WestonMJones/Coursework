#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

int main(int argc, char **argv) {

  struct sockaddr_in servaddr;
  int MSS, RBS, fdsocket;
  fdsocket = socket(AF_INET, SOCK_STREAM, 0);
  unsigned int size1 = sizeof(MSS);
  unsigned int size2 = sizeof(RBS);


  printf("Preconnection:\n");
  getsockopt(fdsocket, IPPROTO_TCP, TCP_MAXSEG, (char *)&MSS, &size1);
  getsockopt(fdsocket,SOL_SOCKET,SO_RCVBUF,(void *)&RBS, &size2);
  printf("Maximum Segment Size: %d\n",MSS);
  printf("Recieve Buffer Size: %d\n",RBS);


  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(80);
  inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

  connect(fdsocket, (struct sockaddr *)&servaddr, sizeof(servaddr));

  printf("\nPostconnection:\n");
  getsockopt(fdsocket, IPPROTO_TCP, TCP_MAXSEG, (char *)&MSS, &size1);
  getsockopt(fdsocket,SOL_SOCKET,SO_RCVBUF,(void *)&RBS, &size2);
  printf("Maximum Segment Size: %d\n",MSS);
  printf("Recieve Buffer Size: %d\n",RBS);


}

