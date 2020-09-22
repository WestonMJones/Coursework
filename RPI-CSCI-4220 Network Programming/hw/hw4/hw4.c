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
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <math.h>


#define BUFFER 1024

// Setup Node struct
struct Node {
	bool intialized;
	char nodeName[BUFFER];
	int id;
	int port;
	int distance;
	int LRU;
};

// And Kbucket struct
struct Kbucket {
	struct Node * nodes;
};


//Declare global vars
char * nodeName;
char * nodeIDseed;
int port, k, nodeID;
bool processing_cmd = false;

// Kbucket structure
struct Kbucket * buckets;

// actual hash table
struct key_val_pair {
	int key;
	int val;
};

struct key_val_pair * table;

// Math formulas
int distance(int first, int sec) {
	int d = first ^ sec;
	return d;
}

int logbase2(int input) {
	int i = floor(log(input)/log(2));
	return i;
}

int hash(char * input) {
	int x = atoi(input);
	x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    x = x % 256;
    return x;

}


// Function that sends the message to the specified address on the specified port
void sendMsg(char * message, char * address, int dest_port) {

	//printf("GOt these args: %s %s %d\n",message,address,dest_port );

	// Open a temp socket -- setup vars
	int sockfd; 
    char buffer[BUFFER]; 
    struct sockaddr_in servaddr, srcaddr; 
    int n; 
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        printf("socket creation failed"); 
        exit(0); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
  
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(dest_port); 
    servaddr.sin_addr.s_addr = inet_addr(address); 

    // Filling info about localhost
    memset(&srcaddr, 0, sizeof(srcaddr));
    srcaddr.sin_family = AF_INET;
    srcaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    srcaddr.sin_port = htons(port+73);
    if (bind(sockfd, (struct sockaddr *) &srcaddr, sizeof(srcaddr)) < 0) {
        perror("bind");
        exit(1);
    }

    // send message 
    int nbytes = sendto(sockfd, (const char*)message, strlen(message), 
           0, (const struct sockaddr*)&servaddr, 
           sizeof(servaddr)); 
  	if(nbytes < 0) {
					printf("ERROR in sendto");
					close(sockfd);
					exit(1);
				}
    // close
    close(sockfd); 
}


// Parse input to extract command and arguments
void parseCommand(char * input, char * cmd, char * arg1, char * arg2, char * arg3) {

	//printf("Got %s as input\n",input );
	int count, delim;
	count = 0;
	delim = 0;

	bzero(cmd,BUFFER);
	bzero(arg1,BUFFER);
	bzero(arg2,BUFFER);
	bzero(arg3,BUFFER);

	for (int i=0;i<strlen(input);i++) {
		if (input[i]==' ') {
			delim++;
			count=0;
		} else {
			if (delim==0) {
				cmd[count]=input[i];
			} else if (delim==1) {
				arg1[count]=input[i];
			} else if (delim==2) {
				arg2[count]=input[i];
			} else if (delim==3) {
				arg3[count]=input[i];
			}
			count++;
		}
	}
}

// Listen for user input and send commands
int client() {

	char message[BUFFER];
	char cmd[BUFFER];
	char arg1[BUFFER];
	char arg2[BUFFER];
	char arg3[BUFFER];
	char toSend[BUFFER];

	while (1) {
		fgets(message,BUFFER,stdin);
		message[strlen(message)-1]='\0';
		//printf("Wrote %s to console\n", message);

		parseCommand(message,cmd,arg1,arg2,arg3);
		//printf("Test: %s %s %s %s\n", cmd,arg1,arg2,arg3);
		if (strcmp(cmd,"CONNECT")==0) {
			// Connect Command

			// Send hello message
			sprintf(toSend,"HELLO %s %d",nodeName,nodeID);
			printf(">?? HELLO %s %x\n", nodeName,nodeID);
			sendMsg(toSend,arg1,atoi(arg2));

		}  else if((strcmp(cmd,"FIND_NODE")==0)) {

			// Keep track of how many searched
			int count = 0;

			

			for (int x=0;x<8;x++) {
				for (int y=0;y<k;y++) {
					if (buckets[x].nodes[y].intialized ==true) {

						if (count>k) {
							break;
						}

						printf("NODE %s %d %x\n",buckets[x].nodes[y].nodeName,buckets[x].nodes[y].port,buckets[x].nodes[y].id);
						sprintf(toSend,"FIND_NODE %d",buckets[x].nodes[y].id);
						sendMsg(toSend,buckets[x].nodes[y].nodeName,buckets[x].nodes[y].port);
						count++;
					}
				}
			}


		} else if ((strcmp(cmd,"FIND_DATA")==0)) {

			// Keep track of how many searched
			int count = 0;

			

			for (int x=0;x<8;x++) {
				for (int y=0;y<k;y++) {
					if (buckets[x].nodes[y].intialized ==true) {

						if (count>k) {
							break;
						}

						printf("NODE %s %d %x\n",buckets[x].nodes[y].nodeName,buckets[x].nodes[y].port,buckets[x].nodes[y].id);
						sprintf(toSend,"FIND_NODE %d",buckets[x].nodes[y].id);
						sendMsg(toSend,buckets[x].nodes[y].nodeName,buckets[x].nodes[y].port);
						count++;
					}
				}
			}

		} else if ((strcmp(cmd,"STORE")==0)) {

			// Search all buckets for best place to store
			int best_i = 0;
			int best_k = 0;
			int min_dist = 256;
			int dist = 0;
			int key = atoi(arg1);
			int val = atoi(arg2);

			for (int x=0;x<8;x++) {
				for (int y=0;y<k;y++) {
					if (buckets[x].nodes[y].intialized==true) {
						//printf("At %d %d. ID is: %x\n",x,y,buckets[x].nodes[y].id );
						dist = distance(buckets[x].nodes[y].id,key);
						if (dist < min_dist) {
							min_dist = dist;
							best_i = x;
							best_k = y;
						}
					}
				}
					
			}

			printf(">%x STORE %d %d\n",buckets[best_i].nodes[best_k].id,key,val);
			sprintf(toSend,"STORE %d %d %d",key,val, nodeID);
			sendMsg(toSend,buckets[best_i].nodes[best_k].nodeName,buckets[best_i].nodes[best_k].port);


		} else if (strcmp(cmd,"QUIT")==0) {

			// Send quit msg to all connected nodes
			for (int x=0;x<8;x++) {
				for (int y=0;y<k;y++) {
					if (buckets[x].nodes[y].intialized ==true) {
						sprintf(toSend,"QUIT %d",nodeID);
						printf(">%x QUIT\n",buckets[x].nodes[y].id);
						sendMsg(toSend,buckets[x].nodes[y].nodeName,buckets[x].nodes[y].port);
					}
				}
			}
			exit(1);
		}
	}
	return 0;


}

// Listen for incoming network traffic
int server() {

	// Setup UDP Select Server

	fd_set read_fds, write_fds;				// temp file descriptors list for select()
	int sockfd;								// socket descriptor
	struct sockaddr_in srv, cli_addr;		// srv used by bind()
	socklen_t clilen = sizeof(cli_addr);
	int nbytes;
	char cmd[BUFFER];
	char arg1[BUFFER];
	char arg2[BUFFER];
	char arg3[BUFFER];

	if ((sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		perror("ERROR opening socket");
		exit(1);
	}
	else {
		//printf("Server : Socket() successful\n");
	}

	// Fill in socket details
	srv.sin_family = AF_INET;
	srv.sin_port = htons(port);
	srv.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr*) &srv, sizeof(srv)) < 0){
		perror("ERROR on binding");
		close(sockfd);
		exit(1);
	}
	else {
		//printf("Server : bind() successful\n");
	}

	// Listen for packets
	while(1) { 			
		char* buf = (char*)malloc(BUFFER);				// message buf
		char* copybuf = (char*)malloc(BUFFER);
		memset(buf, 0, strlen(buf));
		bzero(buf, BUFFER);
		FD_ZERO(&read_fds);
		FD_SET(sockfd, &read_fds);

		int n = select(sockfd+1, &read_fds, &write_fds, 0, 0);
		if(n < 0) {
			perror("ERROR Server : select()\n");
			close(sockfd);
			exit(1);
		}

		if(FD_ISSET(sockfd, &read_fds)) {
			//printf("Server is ready to read\n");
			nbytes = recvfrom(sockfd, buf, BUFFER, 0, (struct sockaddr*)&cli_addr, &clilen);
			if (nbytes < 0) {
				perror("ERROR in recvfrom()");
				close(sockfd);
				exit(1);
			}
			FD_CLR(sockfd, &read_fds);
			//buf[strlen(buf)-1]='\0';
		}

		// Not that we've got a message, see what the command is!

		
		if(strlen(buf) != 0){	
			parseCommand(buf,cmd,arg1,arg2,arg3);


	
			FD_ZERO(&write_fds);
			FD_SET(sockfd, &write_fds);
			if(FD_ISSET(sockfd, &write_fds)){

				// Get IP and port
				int src_port = ntohs(cli_addr.sin_port);
				src_port = src_port-73;
				char* c = (char*) malloc(BUFFER);
				strcpy(c, inet_ntoa(cli_addr.sin_addr));

				if (strcmp(cmd,"HELLO")==0) {
					// Hello Command

					//<2a FIND_NODE 5f
					printf("<%x HELLO %s %x\n",atoi(arg2), arg1,atoi(arg2) );

					// Add NODE to K bucket
					int i = logbase2(distance(nodeID,atoi(arg2)));
					for (int j=0;j<k;j++) {
						if (buckets[i].nodes[j].intialized==false) {
							buckets[i].nodes[j].intialized=true;
							strcpy(buckets[i].nodes[j].nodeName,c);
							buckets[i].nodes[j].id = atoi(arg2);
							buckets[i].nodes[j].port = src_port;
							buckets[i].nodes[j].distance = distance(nodeID,atoi(arg2));
							buckets[i].nodes[j].LRU = 0;
							break;
						}
						buckets[i].nodes[j].LRU++;
					}
					
					// Send MYID Response
					sprintf(buf,"MYID %d",nodeID);
					sendMsg(buf,c,src_port);
					printf(">%x MYID %x\n",atoi(arg2),nodeID);


				} else if((strcmp(cmd,"MYID")==0)) {
					// MYID Command

					printf("<%x MYID %x\n",atoi(arg1),atoi(arg1));


					int i = logbase2(distance(nodeID,atoi(arg1)));
					for (int j=0;j<k;j++) {
						if (buckets[i].nodes[j].intialized==false) {
							buckets[i].nodes[j].intialized=true;
							strcpy(buckets[i].nodes[j].nodeName,c);
							buckets[i].nodes[j].id = atoi(arg1);
							buckets[i].nodes[j].port = src_port;
							buckets[i].nodes[j].distance = distance(nodeID,atoi(arg1));
							buckets[i].nodes[j].LRU = 0;
							break;
						}
						buckets[i].nodes[j].LRU++;
					}

				} else if ((strcmp(cmd,"FIND_NODE")==0)) {

				} else if ((strcmp(cmd,"STORE")==0)) {
					// Search for matching ID


					printf("<%x STORE %s %s\n",atoi(arg3),arg1,arg2);

					// Store data locally!
					for (int i=0;i<100;i++) {
						if (table[i].key!=-1) {
							// Slot is open
							table[i].key=atoi(arg1);
							table[i].val=atoi(arg2);
						}
					}


				} else if (strcmp(cmd,"QUIT")==0) {

					printf("<%x QUIT\n",atoi(arg1) );
					int i = logbase2(distance(nodeID,atoi(arg1)));
					for (int j=0;j<k;j++) {
						if ((buckets[i].nodes[j].id==atoi(arg1))&&(buckets[i].nodes[j].intialized==true)) {
							buckets[i].nodes[j].intialized=false;
						}
					}

				}


				
				FD_CLR(sockfd, &write_fds);
			}

		}
		memset(&buf, 0, sizeof(buf));
		free(buf);
	}
	close(sockfd);
	return 0;

}


int main(int argc, char **argv) {



	// Get arguments
	if (argc == 5) {

		nodeName = argv[1];
		port = atoi(argv[2]);
		nodeID = hash(argv[3]);
		k = atoi(argv[4]);

		//printf("%s %d %s %d\n",nodeName,port,nodeIDseed,k );

	} else {
		printf("Bad arguments!\n");
		return -1;
	}


	// Setup bucket structures

	buckets = calloc(8, sizeof(struct Kbucket));

	for (int i=0;i<8;i++) {
		buckets[i].nodes = calloc(k,sizeof(struct Node));
		for (int x=0;x<k;x++) {
			buckets[i].nodes[x].intialized = false;
		}
	}

	// Setup hash table
	table = calloc(100, sizeof(struct key_val_pair));
	for (int i=0;i<100;i++) {
		// placeholders
		table[i].key = -1;
		table[i].val = -1;
	}


	// Create a separate thread to handle user input
	pthread_t input_thread;
	pthread_create(&input_thread, NULL, client, NULL);
	pthread_detach(input_thread);

	// start listening for other network traffic
	printf("Node %x listening on port %d\n", nodeID, port );
	server();

	return 0;

}