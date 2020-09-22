#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
 
int main(int argc,char **argv)
{

    int port;
    int sockfd,n;
    char sendline[100];
    struct sockaddr_in servaddr;

    printf("Enter a port number: ");
    scanf("%d",&port);
    port = port + 9877;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof servaddr);
 
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
 
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
 
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    printf("Connected on port: %d\n",port );

    int first = 1;

    while(1)
    {
        if (first!=1) {
            printf(">>Enter a message to send: ");
        } else {
            first=0;
        }

        bzero( sendline, 100);
        fgets(sendline,100,stdin);

        write(sockfd,sendline,strlen(sendline)+1);
       


    }
 
}