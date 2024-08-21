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

void display_menu() 
{
    printf("***************************************CHAT APP************************************\n");
    printf("Use the command below:\n");
    printf("myip                              : display IP address of this app\n");
    printf("myport                            : display listening port of this app\n");
    printf("connect <destination> <port no>   : connect to the app of another computer\n");
    printf("list                              : list all the connections of this app\n");
    printf("terminate <connection id>         : terminate a connection\n");
    printf("send <connection id> <message>    : send a message to a connection\n");
    printf("exit                              : close all connections & terminate this app\n");
    printf("**********************************************************************************\n");
}

void show_ip() 
{
    struct ifaddrs *ifaddr, *ifa;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;

        int family = ifa->ifa_addr->sa_family;

        if (family == AF_INET) {
            if (getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) == 0) {
                if (strcmp(ifa->ifa_name, "lo") != 0) {
                    printf("IP Address of this app: %s\n", host);
                    break;
                }
            }
        }
    }

    freeifaddrs(ifaddr);
}

void show_port(int port) 
{
    printf("Listening port of this app: %d\n", port);
}

void list_connections() 
{
    printf("*****************************************\n");
    printf("ID |        IP Address        | Port No.\n");

    if(client_count == 0) {
        printf("*****************************************\n");
    } 
    else {
        printf("-----------------------------------------\n");
        for (int i = 0; i < client_count; i++) {
            printf("%d  |      %s      |  %d\n", i, inet_ntoa(clients[i].address.sin_addr), ntohs(clients[i].address.sin_port));
        }
        printf("*****************************************\n");
    }
}
