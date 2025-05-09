/*
 * File: clients.h
 * Author: ThienBao3617
 * Description: Defines the Client structure and declares functions for managing client connections
 *              in the chat application, including connection establishment, message handling, and termination.
 */

#ifndef CLIENTS_H
#define CLIENTS_H

#include <netinet/in.h>

// Constants
#define MAX_CLIENTS 10  // Maximum number of concurrent clients
#define BUFFER_SIZE 1024  // Buffer size for message transmission

// Structure to store client connection details
struct Client {
    int socket;              // Client socket file descriptor
    struct sockaddr_in address;  // Client address information
};

// Global variables for client management
extern struct Client clients[MAX_CLIENTS];
extern int client_count;

// Function declarations for client operations
void connect_to_server(const char *dest_ip, int dest_port);  // Connect to a remote server
void accept_new_connection(int server_socket);              // Accept a new incoming connection
void handle_client(int client_socket);                      // Handle messages from a client
void terminate_connection(int id);                          // Terminate a client connection by ID
void send_message(int id, const char *message);             // Send a message to a client by ID

#endif