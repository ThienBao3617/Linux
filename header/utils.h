/*
 * File: utils.h
 * Author : ThienBao3617 - skytold
 * Description: Header file for utility functions used throughout the chat application. Provides
 *              function declarations for displaying menus, retrieving IP addresses, and listing connections.
 */

#ifndef UTILS_H
#define UTILS_H

#include <arpa/inet.h>
#include "clients.h" 

#ifndef NI_MAXHOST
#define NI_MAXHOST 102
#endif

#ifndef NI_NUMERICHOST
#define NI_NUMERICHOST 1
#endif

void display_menu();
void show_ip();
void show_port(int port);
void list_connections();

#endif  
