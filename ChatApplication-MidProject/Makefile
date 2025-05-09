# File: Makefile
# Description: Builds the chat application by compiling source files and linking them into an executable.
#
# Targets:
#  - all: Default target to build the chat application
#  - clean: Removes compiled files and the executable
#
# Usage:
#  - Build: make
#  - Clean: make clean

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -Iheader

# Directories
SRCDIR = source
OBJDIR = objects

# Source and object files
SRC = $(SRCDIR)/chat.c $(SRCDIR)/clients.c $(SRCDIR)/utils.c
OBJ = $(OBJDIR)/chat.o $(OBJDIR)/clients.o $(OBJDIR)/utils.o

# Executable name
TARGET = chat

# Default target
all: $(TARGET)

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Clean up build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean