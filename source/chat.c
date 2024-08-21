#include "clients.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <errno.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024


int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    int server_socket, max_sd, activity;
    struct sockaddr_in server_addr;
    fd_set read_fds;

    memset(clients, 0, sizeof(clients));

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    display_menu();
    printf("Application is listening on port %d\n", port);

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(server_socket, &read_fds);
        max_sd = server_socket;

        for (int i = 0; i < client_count; i++) {
            int sd = clients[i].socket;
            if (sd > 0) 
                FD_SET(sd, &read_fds);
            if (sd > max_sd) 
                max_sd = sd;
        }

        activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {}

        // Handle incoming command from stdin (USER)
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            char command[BUFFER_SIZE];
            fgets(command, sizeof(command), stdin);

            char *token = strtok(command, " \n");
            if (token != NULL) {
                if (strcmp(token, "help") == 0) {
                    display_menu();
                } 
                else if (strcmp(token, "myip") == 0) {
                    show_ip();
                } 
                else if (strcmp(token, "myport") == 0) {
                    show_port(port);
                } 
                else if (strcmp(token, "connect") == 0) {
                    char *dest_ip = strtok(NULL, " ");
                    int dest_port = atoi(strtok(NULL, " "));
                    connect_to_server(dest_ip, dest_port);
                } 
                else if (strcmp(token, "list") == 0) {
                    list_connections();
                } 
                else if (strcmp(token, "terminate") == 0) {
                    int id = atoi(strtok(NULL, " "));
                    printf("Terminate peer with ID %d successfully\n", id);
                    printf("A peer has left your chat\n");
                    terminate_connection(id);
                } 
                else if (strcmp(token, "send") == 0) {
                    int id = atoi(strtok(NULL, " "));
                    char *message = strtok(NULL, "\n");
                    send_message(id, message);
                } 
                else if (strcmp(token, "exit") == 0) {
                    for (int i = 0; i < client_count; i++) {
                        close(clients[i].socket);
                    }
                    printf("Exiting...\n");
                    printf("Exiting.........\n");
                    printf("DONE, GOODBYE!!!\n");
                    close(server_socket);
                    exit(EXIT_SUCCESS);
                } 
                else {
                    printf("Invalid command\n");
                }
            }
            printf("Enter your command:\r\n"); 
            fflush(stdout); 
        }

        // Handle new incoming connections
        if (FD_ISSET(server_socket, &read_fds)) {
            accept_new_connection(server_socket);
        }

        // Handle new incoming messages from clients
        for (int i = 0; i < client_count; i++) {
            int sd = clients[i].socket;
            if (FD_ISSET(sd, &read_fds)) {
                handle_client(sd);
            }
        }
    }
    return 0;
}