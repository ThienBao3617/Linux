/*
 * File: utils.h
 * Author: ThienBao3617 
 * Description: Declares utility functions for the chat application, including menu display,
 *              IP/port retrieval, and connection listing.
 */

#ifndef UTILS_H
#define UTILS_H

#include <arpa/inet.h>
#include "clients.h"

// Constants for network interface handling
#ifndef NI_MAXHOST
#define NI_MAXHOST 1025  // Maximum length of hostname
#endif

#ifndef NI_NUMERICHOST
#define NI_NUMERICHOST 1  // Flag for numeric host representation
#endif

// Function declarations for utility operations
void display_menu(void);      // Display the application's command menu
void show_ip(void);           // Display the application's IP address
void show_port(int port);     // Display the application's listening port
void list_connections(void);  // List all active connections

#endif