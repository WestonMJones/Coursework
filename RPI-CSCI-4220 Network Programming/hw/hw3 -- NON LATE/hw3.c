#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>


#define BUFFER 1024

struct User {
    int id;
    char name[20];
    bool operator;
    bool registered;
};

struct Channel {
    char name[20];
    struct User * users;
    int max_users;
    int current_users;
};



bool matchReg(char * string, bool hashtag){
    int i = 0;
    if(strlen(string) < 1) {
        return 0;
    } 

    if(hashtag) {
        if(strlen(string) < 2) {
            return false;
        }
        if(string[i] != '#') {
            return false;
        }
        i++;
    }
    //check the first char is [a-zA-Z]
    if(!isalpha(string[i])) {
        return 0;
        i++;
    } 
    
    //check the rest
    for(; i < strlen(string); i++) {
        if(!(isalnum(string[i]) || string[i] == '_')) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {

    //Setup variables
    int master_socket;
    struct sockaddr_in address;
    socklen_t len = sizeof(address);
    char buffer[BUFFER];
    int max_sd, sd, status, new_socket, resp;
    fd_set readfds;

    // Initialize server variables
    struct User * users = calloc(10, sizeof(struct User));
    struct Channel * channels = calloc(10, sizeof(struct Channel));

    for (int i=0;i<10;i++) {
        users[i].id = 0;
        strncpy(users[i].name, "placeholder", 20);
        users[i].operator = false;
        users[i].registered = false;

        strncpy(channels[i].name, "placeholder", 20);
        channels[i].max_users = 10;
        channels[i].current_users = 0;
        channels[i].users = calloc(10,sizeof(struct User));
    }

    int num_connected = 0;
    int max_connected = 10;

    int num_channels = 0;
    int max_channels = 10;

    // Set server password if given
    char password[20];
    bool password_given = false;
    if (argc == 2) {
        char * arg = argv[1];

        if (arg[0]=='-' && arg[1]=='-' && strlen(arg)>=10) {
            password_given=true;
            for (int i=11;i<strlen(arg);i++) {
                password[i-11]=arg[i];
                password[i-10]='\0';
            }
        }       
    }

    // Create first socket
    if ((master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) {
        perror("Error setting up first socket");
        exit(EXIT_FAILURE);
    }

    // socket details
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( 0 ); // Get assigned port

    //bind socket
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("binding failed");
        exit(EXIT_FAILURE);
    }

    // output port that was chosen
    if (getsockname(master_socket, (struct sockaddr_in *)&address, &len) == -1) {
        perror("getsockname");
    } else {
        printf("Server currently listening on port:  %d\n", ntohs(address.sin_port));
    }

    // Start listening
    if (listen(master_socket, 0) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //get incoming connection
    int addrlen = sizeof(address);

    while (1) {
        //clear socket set
        FD_ZERO(&readfds);

        //add master to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add children
        for ( int i = 0 ; i < max_connected ; i++) {

            sd = users[i].id;

            //if valid socket descriptor then add to list
            if(sd > 0) {
                FD_SET( sd , &readfds);
            }

            //highest file descriptor number will be needed for the select function
            if(sd > max_sd) {
                max_sd = sd;
            }
        }

        // wait for a status change
        status = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((status < 0) && (errno!=EINTR)) {
            printf("select error!");
        }

        //If something happened with master socket , then incoming connection
        if (FD_ISSET(master_socket, &readfds)) {

            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
                perror("accept error");
                exit(EXIT_FAILURE);
            }

            printf("Incoming connection!\n");

            if (send(new_socket, "Please enter a username:\n ", strlen("Please enter a username:\n "), 0) != strlen("Please enter a username:\n ") ) {
                perror("send message error");
            }

            //add new socket to array of sockets
            for (int i = 0; i < max_connected; i++) {
                if (users[i].id == 0 ) {
                    users[i].id = new_socket;
                    break;
                }
            }
            printf("New Socket Added!\n");

        }

        // Incoming message
        for (int i = 0; i < max_connected; i++) {
            //sd = clients[i];
            sd = users[i].id;

            if (FD_ISSET( sd , &readfds)) {

                // Zero buffer
                bzero(buffer,1024);

                //Check if socket closed
                if ((resp = read( sd , buffer, 1024)) == 0) {

                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);

                    printf("Socked Disconnected!\n");
                    // Update data
                    close( sd );
                    users[i].id = 0;

                }

                // Recieve message
                else {

                    // Get rid of trailing new line
                    buffer[strlen(buffer)-1]='\0';
                    char message[1024];


                    //Parse Input
                    int delim = 0;
                    int count = 0;
                    char cmd[10] = "\0";
                    char arg1[20] = "\0";
                    char arg2[1024] = "\0";

                    
                    for (int i=0;i<strlen(buffer);i++) {
                        //printf("Currently on character: %c\n",buffer[i] );

                        if (buffer[i]==' ') {
                            //printf("Detected new word!\n");
                            delim++;
                            if (delim<3) {
                                count=0;                                
                            } else {
                                arg2[count]=' ';
                                count++;
                            }
                        } else {
                            if (delim==0) {
                                cmd[count]=buffer[i];
                                cmd[count+1]='\0';
                                //printf("CMD is now: %s\n",cmd );
                            } else if (delim==1) {
                                arg1[count]=buffer[i];
                                arg1[count+1]='\0';
                                //printf("Arg1 is now: %s\n",arg1 );
                            } else {
                                //printf("On arg2: count is: %d and delim is %d and char is %c\n",count,delim,buffer[i] );
                                arg2[count]=buffer[i];
                                arg2[count+1]='\0';
                                //printf("Arg2 is now: %s\n",arg2 );
                            }
                            count++;
                        }
                    }

                    if (users[i].registered==false) {

                            if (strcmp(cmd,"USER")==0 && strlen(arg1)!=0 && strlen(arg2)==0 ) {

                                bool badName = false;

                                if (matchReg(arg1,false)) {


                                    for (int i=0;i<max_connected;i++) {
                                        if (strcmp(users[i].name,arg1)==0) {
                                            // Name already exists
                                            badName = true;
                                            break;
                                        }

                                    }
                                    
                                } else {
                                    badName = true;
                                }

                                if (!badName) {

                                    users[i].id = sd;
                                    strcpy(users[i].name,arg1);
                                    users[i].operator = false;
                                    users[i].registered = true;
                                    sprintf(message, "Welcome, %s\n", arg1);
                                    send(users[i].id, message, strlen(message),0);
                                } else {
                                    sprintf(message, "Please choose a different, valid username!\n");
                                    send(users[i].id,message,strlen(message),0);

                                }


                        } else {
                            sprintf(message, "Invalid command, please identify yourself with USER.\n");
                            send(users[i].id,message,strlen(message),0);

                            close (sd);
                            users[i].id = 0;
                            strncpy(users[i].name, "placeholder", 20);
                            users[i].operator = false;
                            users[i].registered = false;
                        }

                            


                    } else {
                        // Other commands!
                        if (strcmp(cmd,"LIST")==0 && strlen(arg1)!=0 && strlen(arg2)==0) {
                            // LIST Command for specific channel

                        } else if (strcmp(cmd,"LIST")==0 && strlen(arg1)==0 && strlen(arg2)==0) {
                            // LIST Command for all channels

                        } else if (strcmp(cmd,"JOIN")==0 && strlen(arg1)!=0 && strlen(arg2)==0) {
                            // JOIN Command
                        } else if (strcmp(cmd,"PART")==0 && strlen(arg1)==0 && strlen(arg2)==0) {
                            // GLobal Part command
                        } else if (strcmp(cmd,"PART")==0 && strlen(arg1)!=0 && strlen(arg2)==0) {
                            // Part from specific channel
                        } else if (strcmp(cmd,"OPERATOR")==0 && strlen(arg1)!=0 && strlen(arg2)==0) {
                            // Operator command
                            if (password_given==false) {
                                sprintf(message, "This server doesn't have a password.\n");
                                send(users[i].id,message,strlen(message),0);
                            } else {
                                if (strcmp(arg1,password)==0) {
                                    sprintf(message, "Operator status given.\n");
                                    send(users[i].id,message,strlen(message),0);
                                    users[i].operator=true;
                                } else {
                                    sprintf(message, "Wrong password.\n");
                                    send(users[i].id,message,strlen(message),0);
                                }
                            }


                        } else if (strcmp(cmd,"KICK")==0 && strlen(arg1)!=0 && strlen(arg2)!=0) {
                            // Kick command
                        } else if (strcmp(cmd,"PRIVMSG")==0 && strlen(arg1)!=0 && strlen(arg2)!=0) {
                            // PRIV message command
                        } else if (strcmp(cmd,"QUIT")==0 && strlen(arg1)==0 && strlen(arg2)==0) {
                            // Quit command
                            sprintf(message, "Left server.\n");
                            send(users[i].id,message,strlen(message),0);

                            close (sd);
                            users[i].id = 0;
                            strncpy(users[i].name, "placeholder", 20);
                            users[i].operator = false;
                            users[i].registered = false;
                        } else {
                            // Bad command
                            sprintf(message, "Invalid command.\n");
                            send(users[i].id,message,strlen(message),0);
                        }

                    }

                }
            }
        }
    }

    return 0;

}