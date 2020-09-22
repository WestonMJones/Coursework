/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   server.c
 * Author: siech
 *
 * Created on July 4, 2016, 10:07 AM
 */

#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with pthread

#define SIZE sizeof(int)

#define MAX_NUM 10
#define USAGE_REG 1
#define USAGE_REQ 2
#define USAGE_UNR 3

void *communication_handler(void *);

struct clients {
    int p;
    char ip[20];
};

struct port_data {
    int port;
    int usage;
};

struct sockaddr_in client;
socklen_t addrlen = sizeof (client);
struct port_data port_inf[1];
int server_sock_no;
char tmp_ip[20];
int tmp_p;

int main(int argc, char *argv[]) {
    int *new_sock;
    struct sockaddr_in server;

    //Create socket
    server_sock_no = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server_sock_no == -1) {
        puts("Could not create socket");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    //Bind
    if (bind(server_sock_no, (struct sockaddr *) &server, sizeof (server)) < 0) {
        //print the error message
        perror("An error occurred: bind failed; ");
        return EXIT_FAILURE;
    }

    /* open the file */
    FILE * clients_file = fopen("clients_reg.txt", "w");
    fclose(clients_file);

    //Accept and incoming connection
    puts("\nServer is up, running and wating for incoming messages...\n");

    while (1) {

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = 0;

        if (pthread_create(&sniffer_thread, NULL, communication_handler, (void*) new_sock) < 0) {
            perror("Could not create connection handler");
            return EXIT_FAILURE;
        }

        //Now join the thread , so that we dont terminate before the thread
        pthread_join(sniffer_thread, NULL);

    }

    return EXIT_SUCCESS;
}

/*
 * This will handle connection for each client
 * */
void *communication_handler(void *socket_desc) {
    //Get the socket descriptor
    int buff[1];
    memset(buff, 0, sizeof (buff));
    struct clients registered[10];
    memset(registered, 0, sizeof (registered));
    memset(port_inf, 0, sizeof (struct port_data));
    FILE *clients_file;

    if (recvfrom(server_sock_no, port_inf, sizeof (struct port_data), 0, (struct sockaddr *) &client, &addrlen) > 0) {
        printf("Incoming peer port of communication: ");
        printf("%d\n\n", port_inf[0].port);
    }

    switch (port_inf[0].usage) {
        case USAGE_REG:

            puts("\nCLIENT DETAILS");
            puts("````````````");
            printf("\tIPaddress is: %s\n", inet_ntoa(client.sin_addr));
            printf("\tClient port is: %d\n\n", (int) ntohs(client.sin_port));

            puts("Client seeking to register its details");

            /* open client registration file */
            clients_file = fopen("clients_reg.txt", "a+");
            if (clients_file == NULL) {
                perror("Couldn't open clients_reg.txt for writing.\n");
                exit(0);
            }

            /* register client in file */
            if (strcmp(inet_ntoa(client.sin_addr), "0.0.0.0") != 0) {
                fprintf(clients_file, "%s\t", inet_ntoa(client.sin_addr));
                fprintf(clients_file, "%d\n", (int) port_inf[0].port);
            }

            /* close the file */
            fclose(clients_file);

            /* open the file for reading*/
            clients_file = fopen("clients_reg.txt", "r");
            if (clients_file == NULL) {
                perror("Couldn't open clients_reg.txt for reading.\n");
                exit(0);
            }

            int j = 0;
            while (j < 10) {
                memset(tmp_ip, 0, sizeof (tmp_ip));
                if ((fscanf(clients_file, "%s\t", tmp_ip)) != 1) {
                    break;
                }
                fscanf(clients_file, "%d\n", &tmp_p);

                if (tmp_p == port_inf[0].port)
                    continue;
                strcpy(registered[j].ip, tmp_ip);
                registered[j].p = tmp_p;
                j++;
            }

            puts("... Client registered");

            fclose(clients_file);
            sendto(server_sock_no, registered, sizeof (registered), 0, (struct sockaddr*) &client, sizeof (client));

            puts("... Handler assigned\n");
            break;

        case USAGE_REQ:

            puts("\nCLIENT DETAILS");
            puts("````````````");
            printf("\tIPaddress is: %s\n", inet_ntoa(client.sin_addr));
            printf("\tClient port is: %d\n\n", (int) ntohs(client.sin_port));

            puts("Client requesting for list of peers");

            /* open the file for reading*/
            clients_file = fopen("clients_reg.txt", "r");
            if (clients_file == NULL) {
                perror("Couldn't open clients_reg.txt for reading.\n");
                exit(0);
            }

            j = 0;
            while (j < 10) {
                memset(tmp_ip, 0, sizeof (tmp_ip));
                if ((fscanf(clients_file, "%s\t", tmp_ip)) != 1) {
                    break;
                }
                fscanf(clients_file, "%d\n", &tmp_p);

                if (tmp_p == port_inf[0].port)
                    continue;
                strcpy(registered[j].ip, tmp_ip);
                registered[j].p = tmp_p;
                j++;
            }

            fclose(clients_file);
            sendto(server_sock_no, registered, sizeof (registered), 0, (struct sockaddr*) &client, sizeof (client));

            puts("... Requested list sent to client\n");
            break;

        case USAGE_UNR:

            puts("\nCLIENT DETAILS");
            puts("````````````");
            printf("\tIPaddress is: %s\n", inet_ntoa(client.sin_addr));
            printf("\tClient port is: %d\n\n", (int) ntohs(client.sin_port));

            puts("Client seeking to be unregistered");

            /* open the file for reading*/
            clients_file = fopen("clients_reg.txt", "r");
            if (clients_file == NULL) {
                perror("Couldn't open clients_reg.txt for reading.\n");
                exit(0);
            }

            j = 0;
            while (j < 10) {
                memset(tmp_ip, 0, sizeof (tmp_ip));
                if ((fscanf(clients_file, "%s\t", tmp_ip)) != 1) {
                    break;
                }
                if (strcmp(tmp_ip, "") == 0) break;
                fscanf(clients_file, "%d\n", &tmp_p);
                if (tmp_p != port_inf[0].port) {
                    strncpy(registered[j].ip, tmp_ip, strlen(tmp_ip));
                    registered[j].p = tmp_p;
                    j++;
                }
            }

            fclose(clients_file);

            /* open client registration file */
            clients_file = fopen("clients_reg.txt", "w");
            if (clients_file == NULL) {
                perror("Couldn't open clients_reg.txt for writing.\n");
                exit(0);
            }

            /* register client in file */
            int i = 0;
            while (i < j) {
                fprintf(clients_file, "%s\t", registered[i].ip);
                fprintf(clients_file, "%d\n", registered[i].p);
                i++;
            }

            /* close the file */
            fclose(clients_file);
            puts("... Client unregistered");
    }

    free(socket_desc);
}