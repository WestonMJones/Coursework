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


// Define User structure
struct User {
    bool initialized;
    int id;
    char name[20];
    bool operator;
    bool registered;
};

// Define Channel structure
struct Channel {
    bool initialized;
    char name[20];
    int user_ids[10];
    int max_users;
    int current_users;
};

// Define global variables
struct User * users;
struct Channel * channels;

int num_connected;
int max_connected;

int num_channels;
int max_channels;


// Function that checks validity of user and channel names
bool matchReg(char * string, bool hashtag) {
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

    //check the first char is with the reg exp (a-zA-Z)
    if(!isalpha(string[i])) {
        return 0;
        i++;
    } 

    //check the other parts
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
    num_connected = 0;
    max_connected = 10;

    num_channels = 0;
    max_channels = 10;

    users = calloc(max_connected, sizeof(struct User));
    channels = calloc(max_channels, sizeof(struct Channel));

    for (int i=0;i<max_connected;i++) {
        users[i].initialized=false;
        users[i].id = 0;
        strncpy(users[i].name, "placeholder", 20);
        users[i].operator = false;
        users[i].registered = false;

        channels[i].initialized = false;
        strncpy(channels[i].name, "placeholder", 20);
        channels[i].max_users = max_connected;
        channels[i].current_users = 0;
        for (int j=0;j<max_connected;j++) {
            channels[i].user_ids[j] = 0;
        }
    }

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
    if ((master_socket = socket(AF_INET6 , SOCK_STREAM , 0)) == 0) {
        perror("Error setting up first socket");
        exit(EXIT_FAILURE);
    }

    // socket details -- supports IPv6
    address.sin_family = AF_INET6;
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

        // Check if Users array has to be reallocated
        if (num_connected+3>max_connected) {
            users = realloc(users, (max_connected+10) * sizeof(struct User));
        }

        // Check if channels array has to be reallocated
        if (num_channels+3>max_channels) {
            channels = realloc(channels, (max_channels+10) * sizeof(struct Channel));
        }

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

            if (send(new_socket, "Please enter a username:\n", strlen("Please enter a username:\n"), 0) != strlen("Please enter a username:\n") ) {
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
        for (int c = 0; c < max_connected; c++) {
            //sd = clients[i];
            sd = users[c].id;

            if (FD_ISSET( sd , &readfds)) {

                // Zero buffer
                bzero(buffer,1024);

                //Check if socket closed
                if ((resp = read( sd , buffer, 1024)) == 0) {

                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);

                    printf("Socked Disconnected!\n");
                    // Update data
                    close( sd );
                    users[c].initialized=false;
                    users[c].id = 0;
                    strncpy(users[c].name, "placeholder", 20);
                    users[c].operator = false;
                    if (users[c].registered==true) {
                        users[c].registered = false;
                        num_connected--;
                    }
                    
                
                // Recieve message
                } else {

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


                    if (users[c].registered==false) {
                        // If not yet registered, wait for user command
                        if (strcmp(cmd,"USER")==0 && strlen(arg1)!=0 && strlen(arg2)==0 ) {
                            printf("Got USER Command!\n");

                            bool badName = false;

                            // Check if name fits regex requirements
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
                                // Add user
                                users[c].id = sd;
                                strcpy(users[c].name,arg1);
                                users[c].operator = false;
                                users[c].registered = true;
                                users[c].initialized = true;
                                num_connected++;
                                sprintf(message, "Welcome, %s\n", arg1);
                                send(users[c].id, message, strlen(message),0);

                            } else {

                                sprintf(message, "Please choose a different, valid username!\n");
                                send(users[c].id,message,strlen(message),0);

                            }


                        } else {
                            sprintf(message, "Invalid command, please identify yourself with USER.\n");
                            send(users[c].id,message,strlen(message),0);

                            // Disconnect User
                            close (sd);
                            users[c].id = 0;
                            strncpy(users[c].name, "placeholder", 20);
                            users[c].operator = false;
                            users[c].registered = false;
                            users[c].initialized = false;
                        }




                    } else {

                        // Other commands!
                        if (strcmp(cmd,"LIST")==0 && strlen(arg1)!=0 && strlen(arg2)==0) {
                            // LIST Command for specific channel
                            // CHeck if channel already exists!
                            bool channel_exists = false;


                            for (int i=0;i<max_channels;i++) {
                                if (strcmp(channels[i].name,arg1)==0) {
                                    channel_exists = true;
                                    sprintf(message, "There are currently %d members.\n",channels[i].current_users);
                                    send(users[c].id,message,strlen(message),0);

                                    // To print the users in the channel look for matching IDs
                                    if (channels[i].current_users!=0) {
                                        sprintf(message, "%s members: ",channels[i].name);
                                        send(users[c].id,message,strlen(message),0);
                                        for (int j=0;j<channels[j].max_users;j++) {
                                            if (channels[i].user_ids[j]!=0) {
                                                for (int k=0;k<max_connected;k++) {
                                                    if (channels[i].user_ids[j]==users[k].id) {
                                                        sprintf(message, "%s ",users[k].name);
                                                        send(users[c].id,message,strlen(message),0);
                                                    }
                                                }
                                                
                                            }
                                        }
                                        // Finish with a newline character
                                        sprintf(message, "\n");
                                        send(users[c].id,message,strlen(message),0);
                                    }
                                   
                                }
                            }

                            if (channel_exists==false) {
                                sprintf(message, "Channel doesn't exist!\n");
                                send(users[c].id,message,strlen(message),0);
                            }

                            

                        } else if (strcmp(cmd,"LIST")==0 && strlen(arg1)==0 && strlen(arg2)==0) {
                            // LIST Command for all channels

                            // Count channels
                            int temp_count = 0;
                            for (int i=0;i<max_channels;i++) {
                                if (channels[i].initialized==true) {
                                    temp_count++;
                                }
                            }

                            sprintf(message, "There are currently %d channels\n",temp_count);
                            send(users[c].id,message,strlen(message),0);
                            if (temp_count!=0) {
                                // Print channel names
                                for (int i=0;i<max_channels;i++) {
                                    if (channels[i].initialized==true) {
                                        sprintf(message, "* %s\n",channels[i].name);
                                        send(users[c].id,message,strlen(message),0);
                                    }
                                }
                            }
                            

                        } else if (strcmp(cmd,"JOIN")==0 && strlen(arg1)!=0 && strlen(arg2)==0) {
                            // JOIN Command
                            //printf("Got Join command!\n");
                            if (matchReg(arg1,true)==false) {
                                // Bad format
                                sprintf(message, "Channels must begin a '#' sign!\n");
                                send(users[c].id,message,strlen(message),0);
                            } else {
                                // Proper format

                                // CHeck if channel already exists!
                                bool channel_exists = false;
                                for (int i=0;i<max_channels;i++) {
                                    if (strcmp(channels[i].name,arg1)==0) {
                                        channel_exists = true;
                                    }
                                }

                                if (channel_exists) {
                                    int id_added = 0;
                                    //printf("Channel Exists!\n");
                                    for (int i=0;i<max_channels;i++) {
                                        if (strcmp(channels[i].name,arg1)==0) {
                                            for (int j=0;j<channels[i].max_users;j++) {

                                                // Add user ID to channels ID array
                                                if (channels[i].user_ids[j]==0) {
                                                    channels[i].user_ids[j]=users[c].id;
                                                    channels[i].current_users++;
                                                    
                                                    break;
                                                }
                                            }

                                            // Print X user has joined message to everyone
                                            for (int w=0;w<channels[i].max_users;w++) {
                                                if (channels[i].user_ids[w]!=0) {
                                                    sprintf(message, "%s> %s has joined the channel\n",channels[i].name,users[c].name);
                                                    send(channels[i].user_ids[w],message,strlen(message),0);
                                                }
                                            }
                                        }


                                    }

                                } else {
                                    //printf("Channel doesn't exist!\n");
                                    // Create channel
                                    for (int i = 0; i < max_channels; i++) {
                                        if (channels[i].initialized == false ) {
                                            num_channels++;
                                            channels[i].initialized = true;
                                            strncpy(channels[i].name,arg1,20);
                                            channels[i].user_ids[0] = users[c].id;
                                            channels[i].current_users++;
                                            sprintf(message, "Joined channel %s\n",channels[i].name);
                                            send(users[c].id,message,strlen(message),0);
                                            break;
                                        }
                                    }
                                }

                            }


                        } else if (strcmp(cmd,"PART")==0 && strlen(arg1)==0 && strlen(arg2)==0) {
                            // GLobal Part command

                            // Search all channels for USER Id.
                            for (int i=0;i<max_channels;i++) {
                                for (int j=0;j<channels[i].max_users;j++) {
                                    if (channels[i].user_ids[j]==users[c].id) {

                                        // Inform everyone in channel of departure
                                        for (int e=0;e<channels[i].max_users;e++) {
                                            sprintf(message, "%s> %s has left the channel\n",channels[i].name,users[c].name);
                                            send(channels[i].user_ids[e],message,strlen(message),0);
                                        }
                                        
                                        // Remove User ID
                                        channels[i].user_ids[j]=0;
                                        channels[i].current_users--;
                                        
                                    }
                                }
                            }


                        } else if (strcmp(cmd,"PART")==0 && strlen(arg1)!=0 && strlen(arg2)==0) {
                            // Part from specific channel
                            // CHeck if channel exists!
                            bool channel_exists = false;
                            bool in_channel = false;
                            for (int i=0;i<max_channels;i++) {
                                if (strcmp(channels[i].name,arg1)==0) {
                                    channel_exists = true;
                                    for (int j=0;j<channels[i].max_users;j++) {

                                        // Remove user ID from specified channel
                                        if (channels[i].user_ids[j]==users[c].id) {
                                            channels[i].user_ids[j]=0;
                                            channels[i].current_users--;
                                            in_channel = true;


                                        }
                                    }
                                    if (in_channel) {
                                        // If in channel tell everyone of exit
                                        for (int j=0;j<channels[i].max_users;j++) {
                                            sprintf(message, "%s> %s has left the channel\n",channels[i].name,users[c].name);
                                            send(channels[i].user_ids[j],message,strlen(message),0);
                                           
                                        }
                                        send(users[c].id,message,strlen(message),0);

                                    } else {
                                        sprintf(message, "You are not currently in %s\n",arg1);
                                        send(users[c].id,message,strlen(message),0);
                                    }
                                }
                            }

                            if (channel_exists==false) {
                                sprintf(message, "That channel doesn't exist!\n");
                                send(users[c].id,message,strlen(message),0);
                            }
                        } else if (strcmp(cmd,"OPERATOR")==0 && strlen(arg1)!=0 && strlen(arg2)==0) {
                            // Operator command

                            // Check for password
                            if (password_given==false) {
                                sprintf(message, "This server doesn't have a password.\n");
                                send(users[c].id,message,strlen(message),0);
                            } else {
                                // verify password
                                if (strcmp(arg1,password)==0) {
                                    sprintf(message, "Operator status given.\n");
                                    send(users[c].id,message,strlen(message),0);
                                    users[c].operator=true;
                                } else {
                                    sprintf(message, "Wrong password.\n");
                                    send(users[c].id,message,strlen(message),0);
                                }
                            }


                        } else if (strcmp(cmd,"KICK")==0 && strlen(arg1)!=0 && strlen(arg2)!=0) {
                            // Kick command

                            // Check permissions
                            if (users[c].operator==true) {

                                // Find ID of specified user
                                int bad_user_id = 0;
                                for (int j=0;j<max_connected;j++) {
                                    if (strcmp(users[j].name,arg2)==0) {

                                        bad_user_id = users[j].id;
                                    }
                                }

                                // Search for correct channel
                                for (int l=0;l<max_channels;l++) {
                                    if (strcmp(arg1,channels[c].name)==0) {
                                        for (int u=0;u<channels[l].max_users;u++) {
                                            // Search channel for bad user
                                            if (channels[l].user_ids[u]==bad_user_id) {
                                                for (int e=0;e<channels[l].max_users;e++) {
                                                    // Inform channel of action
                                                    sprintf(message, "%s> %s has been kicked from the channel\n",channels[l].name,arg2);
                                                    send(channels[l].user_ids[e],message,strlen(message),0);
                                                }
                                                channels[c].user_ids[u]=0;
                                                channels[c].current_users--;

                                            }
                                        }
                                    }
                                }
                            } else {
                                sprintf(message, "Insufficient Privilege.\n");
                                send(users[c].id,message,strlen(message),0);
                            }

                        } else if (strcmp(cmd,"PRIVMSG")==0 && strlen(arg1)!=0 && strlen(arg2)!=0) {
                            // PRIV message command
                            if (arg1[0]=='#') {
                                // Broadcast to channel
                                for (int i=0;i<max_channels;i++) {
                                    if (strcmp(channels[i].name,arg1)==0) {
                                        for (int j=0;j<channels[i].max_users;j++) {
                                            sprintf(message, "%s> %s %s\n",arg1,users[c].name,arg2);
                                            send(channels[i].user_ids[j],message,strlen(message),0);
                                        }
                                    }
                                }
                            } else {
                                // Broadcast to individual
                                for (int i=0;i<max_connected;i++) {
                                    if (strcmp(arg1,users[i].name)==0) {
                                        sprintf(message, "%s>> %s\n",arg1,arg2);
                                        send(users[c].id,message,strlen(message),0);

                                        sprintf(message, "<<%s %s\n",users[c].name,arg2);
                                        send(users[i].id,message,strlen(message),0);

                                    }
                                }
                            }
                        } else if (strcmp(cmd,"QUIT")==0 && strlen(arg1)==0 && strlen(arg2)==0) {
                            // Quit command

                            // Remove user from all channels
                            for (int i=0;i<max_channels;i++) {
                                for (int j=0;j<channels[i].max_users;j++) {
                                    if (channels[i].user_ids[j]==users[c].id) {
                                        for (int e=0;e<channels[i].max_users;e++) {
                                            sprintf(message, "%s> %s has left the channel\n",channels[i].name,users[c].name);
                                            send(channels[i].user_ids[e],message,strlen(message),0);
                                        }
                                        
                                        channels[i].user_ids[j]=0;
                                        channels[i].current_users--;
                                        
                                    }
                                }
                            }

                            // Send goodbye message
                            sprintf(message, "Goodbye!\n");
                            send(users[c].id,message,strlen(message),0);

                            // Update data
                            close( sd );
                            users[c].initialized=false;
                            users[c].id = 0;
                            strncpy(users[c].name, "placeholder", 20);
                            users[c].operator = false;
                            users[c].registered = false;
                            num_connected--;

                            
                        } else {
                            // Bad command
                            sprintf(message, "Invalid command.\n");
                            send(users[c].id,message,strlen(message),0);
                        }
                    }
                }
            }
        }
    }

    return 0;

}