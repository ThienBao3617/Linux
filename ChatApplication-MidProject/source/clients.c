/*
 * File: clients.c
 * Author : ThienBao3617 - skytold
 * Description: This file manages client connections. It includes functions for connecting to
 *              other servers, accepting new connections, handling client messages, terminating connections and sending messages.
 *
 * Error Handling:
 *  - Checks socket creation and connection operations and provides meaningful error messages.
 *  - Ensures that connections do not exceed the maximum number of allowed clients.
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

struct Client clients[MAX_CLIENTS];
int client_count = 0;

/*
 * Function: connect_to_server
 * Description: Connects to a server using the specified IP address and port.
 * Input:
 *  dest_ip - IP address of the server
 *  dest_port - Port number of the server
 * Output:
 *  None (prints status messages to stdout)
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

    if (inet_pton(AF_INET, dest_ip, &server_addr.sin_addr) <= 0) {
        printf("Invalid IP address.\n");
        close(sock);
        return;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return;
    } 

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
 * Description: Accepts a new incoming connection and adds it to the list of clients.
 * Input:
 *  server_socket - Socket file descriptor for the server
 * Output:
 *  None (prints status messages to stdout)
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
 * Description: Receives and processes messages from a client. Handles disconnections.
 * Input:
 *  client_socket - Socket file descriptor for the client
 * Output:
 *  None (prints received message or disconnection status to stdout)
 */
void handle_client(int client_socket) 
{
    char buffer[BUFFER_SIZE];
    int bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_read <= 0) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        getpeername(client_socket, (struct sockaddr *)&client_addr, &client_len);
        printf("The peer at port %d has disconnected\n", ntohs(client_addr.sin_port));
        close(client_socket);

        // Notify other clients
        for (int i = 0; i < client_count; i++) {
            if (clients[i].socket == client_socket) {
                terminate_connection(i);
                break;
            }
        }
    } 
    else {
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
 * Description: Terminates the connection with a client identified by the given ID.
 * Input:
 *  id - ID of the client connection to terminate
 * Output:
 *  None (prints status messages to stdout)
 */
void terminate_connection(int id) 
{
    if (id >= 0 && id < client_count) {
        close(clients[id].socket);

        // Move the last client to the terminated position
        if (id != client_count - 1) {
            clients[id] = clients[client_count - 1];
        }

        client_count--;

        // Inform other clients about the termination
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
 * Description: Sends a message to the client identified by the given ID.
 * Input:
 *  id - ID of the client to send the message to
 *  message - Message to send
 * Output:
 *  None (prints status messages to stdout)
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
