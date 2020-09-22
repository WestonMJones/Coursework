/*
 * htons() host to network short
 * htonl() host to network long
 * ntohs() network to host short
 * ntohl() network to host long
 */

/* 
 * File:   peer.c
 * Author: siech
 *
 * Created on July 4, 2016, 10:09 AM
 */

#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h>
#include <stdlib.h> //inet_addr
#include <unistd.h> //
#include <assert.h> //
#include <time.h> //
#include<sys/types.h>
#include<unistd.h>    //write
#include<pthread.h>
#include <rpc/types.h> //for threading , link with pthread
#include <poll.h>

#define USAGE_REG 1
#define USAGE_REQ 2
#define USAGE_UNR 3

void *terminator(void *);
void *requester(void *);
void *chat_initiator(void *);
void *reply_handler(void *);
void *server_consultant(void *);

struct clients {
    int p;
    char ip[20];
};

struct port_data {
    int port;
    int usage;
};

int this_port_no = 0, last_peer = 0, printed = 0;
struct clients registered[10];
struct port_data port_inf[1];

int main(int argc, char *argv[]) {
    int this_socket_no;
    struct sockaddr_in client;
    struct pollfd mypoll = {STDIN_FILENO, POLLIN | POLLPRI};

    //Create socket
    this_socket_no = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (this_socket_no == -1) {
        printf("\nCould not create socket");
    }

    //Initialize random number generator
    srand((unsigned) time(NULL));

    //Generate a random port number
    this_port_no = rand() % 15000 + 10000;

    // Local
    memset(&client, 0, sizeof (struct sockaddr_in));
    client.sin_family = AF_INET;
    client.sin_port = htons(this_port_no);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("\nSocket created at port %d\n\n", this_port_no);

    pthread_t sniffer_thread;
    int *n;
    n = malloc(1);
    *n = this_socket_no;
    int op;

    if (pthread_create(&sniffer_thread, NULL, server_consultant, (void *) n) < 0) {
        perror("Could not create consultant");
        return EXIT_FAILURE;
    }

    //Now join the thread , so that we dont terminate before the thread
    pthread_join(sniffer_thread, NULL);

    close(this_socket_no);

    //Create socket
    this_socket_no = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (this_socket_no == -1) {
        printf("\nCould not create socket");
    }

    // Local
    memset(&client, 0, sizeof (struct sockaddr_in));
    client.sin_family = AF_INET;
    client.sin_port = htons(this_port_no);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    //Bind local to port
    if (bind(this_socket_no, (struct sockaddr *) &client, sizeof (struct sockaddr)) < 0) {
        perror("An error occurred: bind failure.");
        return EXIT_FAILURE;
    }

    for (;;) {

        if (pthread_create(&sniffer_thread, NULL, reply_handler, (void*) n) < 0) {
            perror("Could not create reply handler");
            return EXIT_FAILURE;
        }
        pthread_join(sniffer_thread, NULL);

        op = -1;
        if (!printed) {
            puts("Select an option:\n  1. Initiate chat\n"
                    "  2. Request for list of peers\n"
                    "  3. Exit\n  ---------");
            printed = 1;
            if (poll(&mypoll, 1, 5000)) {
                scanf("%d", &op);
            }
        } else {
            if (poll(&mypoll, 1, 500)) {
                scanf("%d", &op);
            }
        }

        int *n;
        n = malloc(1);
        *n = this_socket_no;

        switch (op) {
            case 1:

                printed = 0;
                if (pthread_create(&sniffer_thread, NULL, chat_initiator, (void*) n) < 0) {
                    perror("Could not create message handler");
                    return EXIT_FAILURE;
                }

                //Now join the thread , so that we dont terminate before the thread
                pthread_join(sniffer_thread, NULL);
                break;

            case 2:

                printed = 0;
                printf("\n");
                if (pthread_create(&sniffer_thread, NULL, requester, (void *) n) < 0) {
                    perror("Could not create requester");
                    return EXIT_FAILURE;
                }

                pthread_join(sniffer_thread, NULL);
                printf("\n\n");
                break;

            case 3:

                printed = 0;
                if (pthread_create(&sniffer_thread, NULL, terminator, (void *) n) < 0) {
                    perror("Could not create terminator");
                    return EXIT_FAILURE;
                }

                //Now join the thread , so that we dont terminate before the thread
                pthread_join(sniffer_thread, NULL);

                close(this_socket_no);

                puts("\nGood bye!\n");
                return EXIT_SUCCESS;

            case -1:
                break;

            default:
                perror("\nInvalid choice");
        }
    }

    //Now join the thread , so that we dont terminate before the thread
    pthread_join(sniffer_thread, NULL);

    puts("\nGood bye!\n");

    close(this_socket_no);
    return EXIT_SUCCESS;
}

void *server_consultant(void *n) {
    int this_socket_no = *(int *) n;
    struct sockaddr_in central_server;
    socklen_t addrlen = sizeof (central_server);

    // Central server
    memset(&central_server, 0, sizeof (struct sockaddr_in));
    central_server.sin_family = AF_INET;
    central_server.sin_port = htons(8888);
    central_server.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(&port_inf, 0, sizeof (struct port_data));
    port_inf[0].port = this_port_no;
    port_inf[0].usage = USAGE_REG;
    sendto(this_socket_no, port_inf, sizeof (struct port_data), 0, (struct sockaddr*) &central_server, sizeof (central_server));

    memset(&registered, 0, sizeof (registered));

    //Receive a list of peers from the central server
    recvfrom(this_socket_no, registered, sizeof (registered), 0, (struct sockaddr *) &central_server, &addrlen);
}

void *terminator(void *n) {
    int this_socket_no = *(int *) n;
    struct sockaddr_in central_server;

    // Central server
    memset(&central_server, 0, sizeof (struct sockaddr_in));
    central_server.sin_family = AF_INET;
    central_server.sin_port = htons(8888);
    central_server.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(&port_inf, 0, sizeof (struct port_data));
    port_inf[0].port = this_port_no;
    port_inf[0].usage = USAGE_UNR;
    sendto(this_socket_no, port_inf, sizeof (struct port_data), 0, (struct sockaddr*) &central_server, sizeof (central_server));
}

void *requester(void *n) {
    int this_socket_no = *(int *) n;
    struct sockaddr_in central_server;
    socklen_t addrlen = sizeof (central_server);

    // Central server
    memset(&central_server, 0, sizeof (struct sockaddr_in));
    central_server.sin_family = AF_INET;
    central_server.sin_port = htons(8888);
    central_server.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(&port_inf, 0, sizeof (struct port_data));
    port_inf[0].port = this_port_no;
    port_inf[0].usage = USAGE_REQ;
    sendto(this_socket_no, port_inf, sizeof (struct port_data), 0, (struct sockaddr*) &central_server, sizeof (central_server));

    memset(&registered, 0, sizeof (registered));

    //Receive a list of peers from the central server
    recvfrom(this_socket_no, registered, sizeof (registered), 0, (struct sockaddr *) &central_server, &addrlen);
    puts("List of peers received from the central server");
    int i;
    for (i = 0; i < 10; i++) {
        if (strcmp(registered[i].ip, "") == 0 || strcmp(registered[i].ip, "0.0.0.0") == 0) {
            continue;
        }
        printf("\n%d.Peer: %s:", i + 1, registered[i].ip);
        printf("%d", registered[i].p);
        last_peer = i + 1;
    }
}

void *chat_initiator(void *n) {
    //Get the socket descriptor
    int i, peer_p;
    struct sockaddr_in peer;
    socklen_t addrlen = sizeof (peer);
    struct sockaddr_in this;
    char msg_to_peer[2000];
    char peer_reply[2000];

    //Create socket
    int this_sock_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (this_sock_desc == -1) {
        printf("\nCould not create socket");
    }

    //Initialize random number generator
    srand((unsigned) time(NULL));

    //Generate a random port number
    int port = rand() % 7000 + 70000;

    // Local
    memset(&this, 0, sizeof (struct sockaddr_in));
    this.sin_family = AF_INET;
    this.sin_port = htons(port);
    this.sin_addr.s_addr = inet_addr("127.0.0.1");

    //Bind local to port
    if (bind(this_sock_desc, (struct sockaddr *) &this, sizeof (struct sockaddr)) < 0) {
        perror("An error occurred: bind failure.");
        exit(0);
    }

    puts("\nList of peers");
    printf("`````````````");
    for (i = 0; i < 10; i++) {
        if (strcmp(registered[i].ip, "") == 0 || strcmp(registered[i].ip, "0.0.0.0") == 0) {
            continue;
        }
        printf("\n%d.Peer: %s:", i + 1, registered[i].ip);
        printf("%d", registered[i].p);
        last_peer = i + 1;
    }

    int p;
    if (last_peer == 0) {
        puts("...does not exist\n");
        return NULL;
    }

    printf("\n\nPick peer no. >> ");
    scanf("%i", &p);

    if (p < 1 || p > last_peer) {
        puts("Peer does not exist");
        exit(0);
    }

    peer_p = registered[p - 1].p;

    //Peer
    memset(&peer, 0, sizeof (struct sockaddr_in));
    peer.sin_family = AF_INET;
    peer.sin_port = htons(peer_p);
    peer.sin_addr.s_addr = inet_addr("127.0.0.1");

    getchar(); //Clear the EOF character from stdin
    while (1) {
        memset(msg_to_peer, 0, sizeof (msg_to_peer));
        memset(peer_reply, 0, sizeof (peer_reply));
        printf("Enter message: ");
        fgets(msg_to_peer, 2000, stdin);

        /* remove newline, if present */
        i = strlen(msg_to_peer) - 1;
        if (msg_to_peer[ i ] == '\n')
            msg_to_peer[i] = '\0';

        if (strcmp(msg_to_peer, "\\w") == 0 || strcmp(msg_to_peer, "\\W") == 0) {
            sendto(this_sock_desc, msg_to_peer, strlen(msg_to_peer), 0, (struct sockaddr*) &peer, sizeof (peer));
            break;
        }

        char ack[23];
        memset(ack, 0, sizeof (ack));

        //Send some message to the peer

        if (sendto(this_sock_desc, msg_to_peer, strlen(msg_to_peer), 0, (struct sockaddr*) &peer, sizeof (peer)) > 0) {
            recvfrom(this_sock_desc, ack, 2000, 0, (struct sockaddr *) &peer, &addrlen);
            printf("%s", ack);
        }

        char recvd_ack[23] = "\t\t\tR&D acknowledged\n";
        //Receive a reply from the peer
        if (recvfrom(this_sock_desc, peer_reply, 2000, 0, (struct sockaddr *) &peer, &addrlen) > 0) {
            if (strcmp(peer_reply, "\\w") == 0 || strcmp(peer_reply, "\\W") == 0) {
                break;
            }
            sendto(this_sock_desc, recvd_ack, strlen(recvd_ack), 0, (struct sockaddr*) &peer, sizeof (peer));
            printf("\nPeer reply : ");
            puts(peer_reply);
        } else {

            break;
        }
    }

    puts("\nInter-peer communication terminated\n");
    puts("Press enter to continue...");
    getchar();

}

void *reply_handler(void *this_socket_no) {
    struct sockaddr_in peer;
    int socket_no = *(int *) this_socket_no;
    socklen_t addrlen = sizeof (peer);
    char peer_reply[2000];
    char message[2000];
    int go_on = 0;

    do {
        memset(message, 0, sizeof (message));
        memset(peer_reply, 0, sizeof (peer_reply));
        char ack[23] = "\t\t\tR&D acknowledged\n";

        struct timeval tv;
        tv.tv_sec = 0; /* seconds */
        tv.tv_usec = 500; /* microseconds */
        if (setsockopt(socket_no, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof (tv)) < 0) {
            printf("Cannot Set SO_RCVTIMEO for socket\n");
        }
        if (recvfrom(socket_no, message, 2000, 0, (struct sockaddr *) &peer, &addrlen) > 0) {
            go_on = 1;
            if (strcmp(message, "\\w") == 0 || strcmp(message, "\\W") == 0) {
                puts("\nInter-peer communication terminated\n");
                puts("Press enter to continue...");
                printed = 0;
                getchar();
                break;
            }
            sendto(socket_no, ack, strlen(ack), 0, (struct sockaddr*) &peer, sizeof (peer));
            printf("\nPeer message: ");
            puts(message);

            printf("Enter reply: ");
            fgets(peer_reply, 2000, stdin);

            /* remove newline, if present */
            int i = strlen(peer_reply) - 1;
            if (peer_reply[ i ] == '\n')
                peer_reply[i] = '\0';

            if (strcmp(peer_reply, "\\w") == 0 || strcmp(peer_reply, "\\W") == 0) {
                sendto(socket_no, peer_reply, strlen(peer_reply), 0, (struct sockaddr*) &peer, sizeof (peer));
                puts("\nInter-peer communication terminated\n");
                puts("Press enter to continue...");
                printed = 0;
                getchar();
                break;
            }

            char recvd_ack[23];
            memset(recvd_ack, 0, sizeof (recvd_ack));

            if (sendto(socket_no, peer_reply, strlen(peer_reply), 0, (struct sockaddr*) &peer, sizeof (peer)) > 0) {
                recvfrom(socket_no, recvd_ack, 2000, 0, (struct sockaddr *) &peer, &addrlen);
                printf("%s", recvd_ack);
            }
        }
    } while (go_on);

}