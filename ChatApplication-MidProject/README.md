# A Chat Application for Remote Message Exchange
## Overview
This project is a peer-to-peer chat application written in C, utilizing **TCP sockets** to enable real-time message exchange between multiple clients on a Linux system. It supports up to 10 concurrent connections, managed through I/O multiplexing with **select()**, and provides a **CLI** for user interaction.
## Link of Project's Requirement
- https://docs.google.com/document/d/1_hkphcnSYAvj2U1Cd7mMGs-KA7oBg5R8Y031sHh61Lg/edit
## Table of Contents
- Features

- Prerequisites

- Installation

- Building the Application

- Running the Application

- Usage

- Cleaning Up

## Features
- Dual client-server architecture in a single program

- Supports commands: **myip, myport, connect, list, terminate, send, exit**

- Handles up to 10 concurrent clients using **select()** for I/O multiplexing

- Robust error handling for invalid IPs, self-connections, and disconnections

- Tested across multiple machines for reliable communication


## Prerequisites
- **GCC**: GNU Compiler Collection for compiling C programs

- **Make**: Build automation tool for compiling the application

- **Git**: Version control system to clone the repository

#### Installing Prerequisites

    sudo apt-get update
    sudo apt-get install gcc make git

For other operating systems, refer to your package manager's instructions.

## Installation
Clone this repository to your local machine:

    git clone https://github.com/ThienBao3617/Linux.git
    cd Linux

## Building the Application
The project includes a **Makefile** to automate the build process. To build the application, run:

    make

This compiles the **source** files in the source directory, generates **object** files in the objects directory, and creates the **chat** executable.

## Makefile Overview
- Compiler: **gcc** with flags **-Wall -g -Iheader**

- Directories:

    - Source: **source (chat.c, clients.c, utils.c)**

    - Objects: **objects (chat.o, clients.o, utils.o)**

- Executable: **chat**

## Running the Application
Run the chat application on a specified port:

    ./chat <port>

Example: To run on port **4000**:

    ./chat 4000

Start additional instances on different ports (e.g., 5000, 6000) to simulate multiple clients.

## Usage
The application provides the following CLI commands:

- **myip**: Display the IP address of this instance

- **myport**: Display the listening port of this instance

- **connect < destination > < port >**: Connect to another instance

- **list**: List all active connections

- **terminate < connection id >**: Terminate a connection by ID

- **send < connection id > < message >**: Send a message to a connection

- **exit**: Close all connections and terminate the application

## Cleaning Up
To remove compiled files and the executable, run:

    make clean

