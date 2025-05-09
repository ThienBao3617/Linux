/*
 * File: clients.c
 * Author: ThienBao3617 
 * Description: Manages client connections for the chat application. Provides functions to connect
 *              to servers, accept new connections, handle messages, terminate connections, and send messages.
 */

#include "clients.h"
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

// Global client array and counter
struct Client clients[MAX_CLIENTS];
int client_count = 0;

/*
 * Function: connect_to_server
 * Description: Establishes a connection to a remote server at the specified IP and port.
 * Parameters:
 *  - dest_ip: IP address of the destination server
 *  - dest_port: Port number of the destination server
 */
void connect_to_server(const char *dest_ip, int dest_port) 
{
    struct sockaddr_in server_addr;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("Socket creation failed");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(dest_port);

    // Convert IP address to binary form
    if (inet_pton(AF_INET, dest_ip, &server_addr.sin_addr) <= 0) {
        printf("Invalid IP address.\n");
        close(sock);
        return;
    }

    // Attempt to connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return;
    } 

    // Add the new connection to the client list
    if (client_count < MAX_CLIENTS) {
        clients[client_count].socket = sock;
        clients[client_count].address = server_addr;
        client_count++;
        printf("Successfully connected. Ready for data transmission\n");
    } 
    else {
        printf("Maximum clients reached. Connection rejected.\n");
        close(sock);
    }
}

/*
 * Function: accept_new_connection
 * Description: Accepts a new incoming connection and adds it to the client list.
 * Parameters:
 *  - server_socket: Socket file descriptor of the server
 */
void accept_new_connection(int server_socket) 
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int new_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (new_socket < 0) 
    {
        perror("Accept failed");
        return;
    }

    // Add the new client to the list if capacity allows
    if (client_count < MAX_CLIENTS) {
        clients[client_count].socket = new_socket;
        clients[client_count].address = client_addr;
        client_count++;
        printf("Accepted a new connection from address: %s, setup at port: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    } 
    else {
        printf("Maximum clients reached. Connection rejected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        close(new_socket);
    }
}

/*
 * Function: handle_client
 * Description: Processes messages from a client and handles disconnections.
 * Parameters:
 *  - client_socket: Socket file descriptor of the client
 */
void handle_client(int client_socket) 
{
    char buffer[BUFFER_SIZE];
    int bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_read <= 0) {
        // Client disconnected
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        getpeername(client_socket, (struct sockaddr *)&client_addr, &client_len);
        printf("The peer at port %d has disconnected\n", ntohs(client_addr.sin_port));
        close(client_socket);

        // Remove the client from the list
        for (int i = 0; i < client_count; i++) {
            if (clients[i].socket == client_socket) {
                terminate_connection(i);
                break;
            }
        }
    } 
    else {
        // Process received message
        buffer[bytes_read] = '\0';
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        getpeername(client_socket, (struct sockaddr *)&client_addr, &client_len);

        printf("*****************************************\n");
        printf("* Message received from: %s\n", inet_ntoa(client_addr.sin_addr));
        printf("* Sender's port: %d\n", ntohs(client_addr.sin_port));
        printf("* Content: %s\n", buffer);
        printf("*****************************************\n");
    }
}

/*
 * Function: terminate_connection
 * Description: Terminates a client connection by ID and notifies other clients.
 * Parameters:
 *  - id: ID of the client connection to terminate
 */
void terminate_connection(int id) 
{
    if (id >= 0 && id < client_count) {
        close(clients[id].socket);

        // Shift the last client to the terminated position
        if (id != client_count - 1) {
            clients[id] = clients[client_count - 1];
        }

        client_count--;

        // Notify other clients of the termination
        for (int i = 0; i < client_count; i++) {
            char msg[BUFFER_SIZE];
            snprintf(msg, sizeof(msg), "Connection %d has been terminated.\n", id);
            send(clients[i].socket, msg, strlen(msg), 0);
        }

    } 
    else {
        printf("Invalid connection ID.\n");
    }
}

/*
 * Function: send_message
 * Description: Sends a message to a client by ID.
 * Parameters:
 *  - id: ID of the client to send the message to
 *  - message: Message content to send
 */
void send_message(int id, const char *message) 
{
    if (id >= 0 && id < client_count) {
        send(clients[id].socket, message, strlen(message), 0);
        printf("Sent message successfully\n");
    } 
    else {
        printf("Invalid connection ID.\n");
    }
}