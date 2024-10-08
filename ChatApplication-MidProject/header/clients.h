/*
 * File: clients.h
 * Author : ThienBao3617 - skytold
 * Description: Header file for client management functions. Defines the structure for client data
 *              and declares functions for managing client connections.
 *
 * Structures:
 *  - Client: Contains socket information and address details for each client.
 */

#include <netinet/in.h> 
#ifndef CLIENTS_H
#define CLIENTS_H

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

struct Client {
    int socket;
    struct sockaddr_in address;
};

extern struct Client clients[MAX_CLIENTS];
extern int client_count;

void connect_to_server(const char *dest_ip, int dest_port);
void accept_new_connection(int server_socket);
void handle_client(int client_socket);
void terminate_connection(int id);
void send_message(int id, const char *message);

#endif
