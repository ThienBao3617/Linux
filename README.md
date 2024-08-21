# A Chat Application for Remote Message Exchange
## Overview
This repository contains a chat application built in C. The application supports multiple clients communicating over TCP sockets. It features basic commands for managing connections and sending messages. This README file provides detailed documentation on how to install prerequisites, build the application, and run it.

## Table of Contents
1. Contributors
2. Prerequisites
3. Installation
4. Building the Application
5. Running the Application
6. Usage
7. Cleaning Up

## Contributors
- ThienBao3617: Responsible for overall design and implementation of the chat application project, including core functionality and command handling.

## Prerequisites
Before you can build and run the application, you need to have the following installed on your system:

- GCC: The GNU Compiler Collection for compiling C programs.
- Make: Build automation tool to compile the application.

## Installing Prerequisites
To install GCC and Make on Ubuntu, you can use the following command in your terminal:

    sudo apt-get update
    sudo apt-get install gcc make

For other operating systems, please refer to the appropriate package manager or installation instructions.

## Installation
Clone this repository to your local machine:

    git clone https://github.com/ThienBao3617/Linux.git
    cd Linux

## Building the Application
The application uses a Makefile to manage the build process. The Makefile handles compiling the source code and linking the object files to create the final executable.

To build the application, run:

    make

This command will compile the source code files located in the source directory, create object files in the objects directory, and link them to produce the executable binary chat in the root directory.

## Makefile Details
- Compiler and Flags: The Makefile uses gcc with the flags -Wall -g -Iheader for compiling.
- Directories:   
    - SRCDIR: Directory containing source files (source).   
    - OBJDIR: Directory for object files (objects).
- Source Files:
    - chat.c
    - clients.c
    - utils.c
- Object Files:
    - chat.o
    - clients.o
    - utils.o
- Executable: The final executable is named chat.

## Running the Application
To run the chat application, use the following command format:

    ./chat <port>

Replace <port> with the port number you wish the server to listen on. This will start the chat application server on the specified port.

***Example***  
To run the application on port 4000, use:

    ./chat 4000

For more other ports (clients), keep using: 

    ./chat 5000
    ./chat 6000
    ...

## Usage
Once the application is running, you can use the following commands within the chat application:
- myip: Displays the current IP Address of the server.
- myport: Displays the port number on which the server is running.
- connect < destination > < port >: Connects to another server at < destination > on < port >.
- list: Lists all active connections with their IDs, IP addresses, and port numbers.
- terminate < id >: Terminates the connection with the specified ID.
- send < id > < message >: Sends a message to the connection with the specified ID.
- exit: Close all connections and terminate the application

## Cleaning Up
To clean up the build artifacts and remove compiled object files and the executable, use:

    make clean

This command will delete the objects directory and the chat executable.