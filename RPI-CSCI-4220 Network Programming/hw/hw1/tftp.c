// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/errno.h>

// RRQ =1, WRQ = 2, DATA = 3, ACK = 4, ERROR = 5
// REFERENCE FOR OP CODES

// Helpful way way of organizing types of messages into structures
typedef union {

     uint16_t OP_CODE;

     struct {
          uint16_t opcode;
          uint16_t block_number;
          uint8_t data[512];
     } DATA;

     struct {
          uint16_t opcode;
          uint16_t block_number;
     } ACK;

     struct {
          uint16_t opcode;
          uint8_t filename[514];
     } REQUEST;

     struct {
          uint16_t opcode;
          uint16_t error_code;
          uint8_t error_msg[512];
     } ERROR;
} tftp_msg;

// Sends errors to client
ssize_t sendError(int s, int code, char *detail, struct sockaddr_in *sock, socklen_t s_len) {

     tftp_msg m;
     ssize_t c;

     if (!strlen(detail) <= 512) {
          fprintf(stdout,"Server error: string is too long\n");
          return -1;
     }

     // RRQ =1, WRQ = 2, DATA = 3, ACK = 4, ERROR = 5
     m.ERROR.error_code = code;
     m.OP_CODE = htons(5);
     strcpy(m.ERROR.error_msg, detail);


     int msg_size = strlen(detail) + 5;

     if (!(c = sendto(s, &m, msg_size, 0, (struct sockaddr *) sock, s_len)) >= 0) {
          fprintf(stdout,"Server error: problem in sendTo()");
     }

     return c;
}

// Handles messages from client
void handleRequest(tftp_msg *m, ssize_t len, struct sockaddr_in *client_sock, socklen_t s_len) {

     int s;
     struct timeval tv;
     char *fname; 
     char *mode_s;
     char *end;
     
     //open new socket
     if ((s = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
          fprintf(stdout,"Server error: Problem with socket()");
          exit(1);
     }

     //set timeout vals
     tv.tv_sec  = 1;
     tv.tv_usec = 0;

     if (setsockopt (s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
          fprintf(stdout,"problem with setsockopt\n");
     }

     if (setsockopt (s, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0) {
          fprintf(stdout,"problem with setsockopt\n");
     }

     // Get fname and opcode
     fname = m->REQUEST.filename;

     // Read request
     uint16_t OP_CODE=ntohs(m->OP_CODE);

     // RRQ =1, WRQ = 2, DATA = 3, ACK = 4, ERROR = 5
     if(OP_CODE==1) {

          if( access( fname, F_OK ) != -1 ) {

               // read file
               FILE *file;
               file = fopen(fname, "r");
               if (file == NULL) {
                    fprintf(stdout,"Server error: Problem with fopen()");
                    sendError(s, htons(0), strerror(errno), client_sock, s_len);
                    exit(1);
               }

               // go in 512 byte increments
               uint16_t blockNum=0;
               int needClose=0;

               while(needClose==0) {

                    int count;
                    ssize_t len_r=0;
                    ssize_t n=0;
                    tftp_msg m2;
                    uint8_t read[512];
                    for(int i = 0; i<512;i++){
                         read[i]='\0';
                    }

                    // keep hold of data
                    len_r=fread(read,1,512,file);
                    blockNum+=1;

                    // check if need to send moar packets
                    if (!(len_r>=512)) {
                         needClose=1;
                    }

                    for(count=0;count<10;count++) {

                         tftp_msg temp;
                         struct sockaddr_in hold_socket;
                         // RRQ =1, WRQ = 2, DATA = 3, ACK = 4, ERROR = 5
                         temp.OP_CODE = htons(3);
                         temp.DATA.block_number = htons(blockNum);

                         for(int i = 1; i<513;i++){
                              temp.DATA.data[i-1]='\0';
                         }

                         memmove(temp.DATA.data, read, len_r);

                         //send 

                         int total_len = len_r+4;
                         n = sendto(s, &temp, total_len, 0, (struct sockaddr *) client_sock, s_len);
                         if (n<0) {
                              fprintf(stdout, "Server error: Problem with sendTo()");
                              exit(1);
                         }

                         //get ack
                         n=recvfrom(s,&m2,sizeof(m2),0,(struct sockaddr *) &hold_socket,&s_len);


                         // check response
                         if (n>=4) {
                              n=0;
                              break;
                         } else {
                              if (n>=0 && n<4) {
                                   fprintf(stdout, "Server error: got bad response - 1");
                                   exit(1);
                              }  
                         }
                    }

                    // check count
                    if (count==9) {
                         fprintf(stdout, "Server error: timeout");
                         exit(1);
                    }
               
                    // RRQ =1, WRQ = 2, DATA = 3, ACK = 4, ERROR = 5
                    if (ntohs(m2.OP_CODE)!=4) {
                         fprintf(stdout, "Server error: got bad response - 2");
                         exit(1);
                    }

                    if(ntohs(m2.ACK.block_number)!=blockNum) {
                         fprintf(stdout, "Server error: got bad response - 3");
                         sendError(s,htons(0),"Bad Ack code",client_sock,s_len);
                         exit(1);
                    }

                    // RRQ =1, WRQ = 2, DATA = 3, ACK = 4, ERROR = 5
                    if(ntohs(m2.OP_CODE)==5){
                         fprintf(stdout, "Server error: got bad response - 4");
                         exit(1);
                    }
               }
          } else {
               //file does not exist
               sendError(s,htons(1),"invalid file name",client_sock,s_len);
               exit(1);
          }

     // Handle writes
     // RRQ =1, WRQ = 2, DATA = 3, ACK = 4, ERROR = 5
     }
     if(OP_CODE==2) {
          
          FILE *file;



          file = fopen(fname, "w");

          if (file == NULL) {
               fprintf(stdout, "Server error: problem with fopen()");
               sendError(s, htons(0), strerror(errno), client_sock, s_len);
               exit(1);
          }


          //read in 512 byte increments

          tftp_msg a;

          uint16_t blockNum=0;


          // RRQ =1, WRQ = 2, DATA = 3, ACK = 4, ERROR = 5
          a.OP_CODE=htons(4);
          a.ACK.block_number=htons(blockNum);
          ssize_t n=0;

          //send first ACK
          n=sendto(s,&a,sizeof(a.ACK),0,(struct sockaddr *) client_sock,s_len);
          if (!(n>=0)) {
               printf("got bad response\n");
               exit(1);
          }

          // Run the loop until no more data left
          int needClose=0;
          while (needClose==0) {
               int count;
               tftp_msg m2;

               for(count=0; count<10;count++) {
                    struct sockaddr_in hold_socket;

                    
                    n=recvfrom(s,&m2,sizeof(m2),0,(struct sockaddr *) &hold_socket,&s_len);

                    if (n>=4) {
                         break;
                    } else {
                         if (n<4&&n>=0) {
                              sendError(s, htons(0), "Invalid request size", client_sock, s_len);
                              exit(1);  
                         }
                    }

                    a.ACK.block_number=htons(blockNum);
                    n=sendto(s,&a,sizeof(a.ACK),0,(struct sockaddr *) client_sock,s_len);
                    if (!(n>=0)) {
                         fprintf(stdout, "Killed Transfer");
                         exit(1);
                    }
               }

               if(count==9){
                    fprintf(stdout, "Server error: timeout");
                    exit(1);
               }

               blockNum++;

               if (strlen(m2.DATA.data)<512){
                    needClose=1;
               }


               n = fwrite(m2.DATA.data, 1, n - 4, file);
               if (!(n>=0)) {
                    fprintf(stdout, "Server error: problem with fwrite()");
                    exit(1);
               }
               a.ACK.block_number=htons(blockNum);
               n=sendto(s,&a,sizeof(a.ACK),0,(struct sockaddr *) client_sock,s_len);

               if (n < 0) {
                    printf("Server error: Transfer killed\n");
                    exit(1);
               }
          }

          printf("Success\n");
          fclose(file);
          close(s);
     }
}


int main() {

    ssize_t n;
    char buf[512];

    socklen_t sockaddr_len;
    int server_socket;
    struct sockaddr_in sock_info;
    sockaddr_len = sizeof(sock_info);

    unsigned short int opcode;
    unsigned short int * opcode_ptr;

    // Initialize socket and get port
    memset(&sock_info, 0, sockaddr_len);

    sock_info.sin_addr.s_addr = htonl(INADDR_ANY);
    sock_info.sin_port = htons(0);
    sock_info.sin_family = PF_INET;
    getsockname(server_socket, (struct sockaddr *)&sock_info, &sockaddr_len);
    printf("Server running on port number: %d\n", ntohs(sock_info.sin_port));

    // Loop infinitely to handle requests
    while(1>0) {

          struct sockaddr_in client_sock;
          socklen_t s_len = sizeof(client_sock);
          tftp_msg m;

          // Recieve a message and create a message object
          n = recvfrom(server_socket, &m, sizeof(m), 0, (struct sockaddr *) &client_sock, &s_len);

          if (!(n >= 0)) {
               // if(errno == EINTR) goto intr_recv;
               fprintf(stdout, "Server error: did't recieve\n");
               exit(-1);
          }

          opcode = ntohs(m.OP_CODE);

          if(opcode != 1 && opcode != 2) {
               /* Illegal TFTP Operation */
               *opcode_ptr = htons(5);
               *(opcode_ptr + 1) = htons(4);
               *(buf + 4) = 0;

               intr_send:
               n = sendto(server_socket, buf, 5, 0, (struct sockaddr *)&sock_info, sockaddr_len);
               if(n < 0) {
                    n = sendto(server_socket, buf, 5, 0, (struct sockaddr *)&sock_info, sockaddr_len);
                    perror("sendto");
                    exit(-1);
               }
          } else {
               if(fork() == 0) {
                    close(server_socket);
                    handleRequest(&m, n, &client_sock, s_len);
                    exit(0);
               } else {
                    /* Parent - continue to wait */
               }
          } 
     }
     return 0;
}