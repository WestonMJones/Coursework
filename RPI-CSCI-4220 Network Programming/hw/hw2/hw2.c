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
#define MAX_CLIENTS 5

// Generates the output message upon a valid guess
char* process_guess(char * user, char * guess, char * word) {

   // Initialize variables
   unsigned int correct = 0;
   unsigned int placed = 0;
   unsigned int length = strlen(guess);

   // See if words are in right place
   for (unsigned int i=0;i<length;i++) {
      if (guess[i]==(word[i])) {
         placed++;
      }
   }

   // Keep track of "used" letters when calculating accuracy of guess
   int tried[length];

   // Initialize placeholder values of -1
   for (int i=0;i<length;i++) {
      tried[i]=-1;
   }

   // Keep track of next unused entry in array
   unsigned int free_position = 0;


   for (unsigned int a=0;a<length;a++) {
      for (unsigned int b=0;b<length;b++) {

         if (guess[a]==word[b]) {

            // Check if letter in secret word has already been "used"
            bool already = false;
            for (unsigned int x=0;x<length;x++) {
            
               if (b==tried[x]) {
                  already = true;
               }
            }

            // If not already used, count it as correct word and update "used" array
            if (!already) {
               tried[free_position]=b;
               free_position++;
               correct++;
               break;
            }

         }

      }
   }

   // Generate output message
   char temp[3000];
   int act = snprintf(temp,3000,"%s guessed %s: %d letter(s) were correct and %d letter(s) were correctly placed.\n",user,guess,correct,placed);
   return strdup(temp);
}

// Function that reads the input dictionary 
// and semi-randomly chooses a word
char* pick_word(char *fname, unsigned int max_word_size) {

   // Initalize variables
   unsigned int current_line = 0;
   unsigned int selected_length = 0;

   char current_word[max_word_size];
   char selected_word[max_word_size];

   selected_word[0] = '\0';

   // Seed random number generator
   srand48(time(0));

   // Read dictionary file
   FILE * f = fopen(fname,"r");
   while (fgets(current_word, sizeof(current_word), f)) {

      // Replace currently selected word
      // Less chance of it happening the farther down we are
      if (drand48() < (1.0 / current_line)) {
         strcpy(selected_word, current_word);
      }
      current_line++;
   }

   fclose(f);

   selected_length = strlen(selected_word);

   // Trim word
   if (selected_length > 0 && selected_word[selected_length-1] == '\n') {
      selected_word[selected_length-1] = '\0';
   }

   // Convert to lowercase
   int i=0;
   char c;
   while (selected_word[i]) {
      c=selected_word[i];
      selected_word[i] = tolower(c);
      i++;
   }

   return strdup(selected_word);
}



// Compare string to see if equal
// Accounts for the trailing characters sometimes at the end of 
// buffers
int compare_string(char * first, char * second) {

   bool equal = true;
   if (strlen(first)>strlen(second)) {
      for (int i=0;i<strlen(second);i++) {
         if (first[i]!=second[i]) {
            equal = false;
         }
      }
   } else {
      for (int i=0;i<strlen(first);i++) {
         if (first[i]!=second[i]) {
            equal = false;
         }
      }
   }
   return equal;
}

int main(int argc, char **argv) {

   //Setup variables
   int master_socket;
   struct sockaddr_in address;
   socklen_t len = sizeof(address);
   char buffer[BUFFER];
   int max_sd, sd, status, new_socket, resp;
   char usernames[5][20] = {
      "placeholder",
      "placeholder",
      "placeholder",
      "placeholder",
      "placeholderr"
   };
   bool registered[5] = {false,false,false,false,false};
   int num_connected = 0;
   int clients[5] = {0,0,0,0,0};
   fd_set readfds;

   // Check arguements
   if (argc != 3) {
      printf("Args = Dict file name & max word size\n");
      exit(1);
   }

   // Choose secret word
   char * filename = argv[1];
   unsigned int word_size = atoi(argv[2]);
   char * chosen = pick_word(filename,word_size);
   int chosen_length = strlen(chosen);

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

   // Write secret word
   printf("Secret word is %s (Length %d)!\n",chosen,chosen_length );

   // Specify max amount of connections
   if (listen(master_socket, 5) < 0) {
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
      for ( int i = 0 ; i < MAX_CLIENTS ; i++) {
      
         sd = clients[i];

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
         if (send(new_socket, "Please enter a username: ", strlen("Please enter a username: "), 0) != strlen("Please enter a username: ") ) {
            perror("send message error");
         }


         //add new socket to array of sockets
         for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] == 0 ) {
               clients[i] = new_socket;
               registered[i] = 0;
               break;
            }
         }
      }

      // Incoming message
      for (int i = 0; i < MAX_CLIENTS; i++) {
         sd = clients[i];

         if (FD_ISSET( sd , &readfds)) {

            // Zero buffer
            bzero(buffer,1024);

            //Check if socket closed
            if ((resp = read( sd , buffer, 1024)) == 0) {

               getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
               printf("%s disconnected!\n" , usernames[i]);

               // Update data
               close( sd );
               clients[i] = 0;
               registered[i] = false;
               num_connected--;
               char temp[] = "placeholder";
               strcpy(usernames[i],temp);
            }

            // Recieve message
            else {
            
               // Get rid of trailing new line
               buffer[strlen(buffer)-1]='\0';

               // If username not yet registered
               if (registered[i]==false) {

                  // Check to see if username has been taken
                  int user_take = false;


                  for (int u=0;u<5;u++) {
                     if (compare_string(buffer,usernames[u])==true) {
                        user_take = true;
                     }
                  }

                  // If not taken
                  if (user_take==false) {
                     strcpy(usernames[i],buffer);
                     //usernames[i][strlen(buffer)-1]="\0";
                     registered[i]=true;
                     num_connected++;
                     char msg1[100];
                     printf("User %s has joined the game!\n",usernames[i] );
                     snprintf(msg1,100,"There are %d players currently playing and word length is %d\n",num_connected,chosen_length);
                     send(sd,msg1,strlen(msg1),0);

                     // if taken
                  } else {
                     printf("New connection chose existing username!\n");
                     send(sd , "Username taken, try another username\n" , strlen("Username taken, try another username\n") , 0 );
                  }




               } else {
                  // Username has been registered

                  // Convert guess to lowercase
                  int g=0;
                  char j;

                  while (buffer[g]) {
                     j=buffer[g];
                     buffer[g]= (tolower(j));
                     g++;
                  }
                  //buffer[resp] = '\0';
                  //buffer[strlen(buffer)-1] = '\0';
                  //printf("%s is counted as %d in length\n", buffer, strlen(buffer) );

                  // GUess invalid length
                  if (strlen(buffer)!=chosen_length) {

                     send(sd, "Guess is wrong length =(\n",strlen("Guess is wrong length =(\n"),0);

                     // Guess of valid length
                  } else {

                     // Guess correct
                     if (compare_string(buffer,chosen)==true) {

                        char msg3[1024];
                        snprintf(msg3,1024,"%s has correctly guessed the word %s\n",usernames[i],chosen);

                        // Reset Game
                        for (int s=0;s<MAX_CLIENTS;s++) {
                           if (registered[s]==true) {
                              send(clients[s],msg3,strlen(msg3),0);
                              close( clients[s] );
                              clients[s] = 0;
                              registered[s] = false;
                              num_connected--;
                              char temp[] = "placeholder";
                              strcpy(usernames[s],temp);
                           }
                        }

                        chosen = pick_word(filename,word_size);
                        chosen_length = strlen(chosen);
                        printf("New secret word is %s (Length %d)!\n",chosen,chosen_length );

                     // Guess incorect
                     } else {
                        char * msg2 = process_guess(usernames[i],buffer,chosen);

                        for (int s=0;s<MAX_CLIENTS;s++) {
                           // send message to every client
                           if (registered[s]==true) {
                              send(clients[s],msg2,strlen(msg2),0);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

   return 0;

}