# File: Makefile
# Description: Makefile to compile the chat application. It handles the compilation of
#              multiple C source files and links them into a single executable binary.
#
# Targets:
#  - all: Compiles all source files and creates the executable.
#  - clean: Removes compiled object files and the executable.
#
# Usage:
#  - To compile the application, run: make
#  - To clean the directory, run: make clean
#
# Error Handling:
#  - Checks if the compiler and linker commands execute successfully.
#
# Variables:
#  - CC: Compiler used for building the program (default: gcc).
#  - CFLAGS: Compiler flags for warnings and debugging.
#  - OBJ: Object files generated from the source files.

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -Iheader

# Directories
SRCDIR = source
OBJDIR = objects

# Source files
SRC = $(SRCDIR)/chat.c $(SRCDIR)/clients.c $(SRCDIR)/utils.c

# Object files
OBJ = $(OBJDIR)/chat.o $(OBJDIR)/clients.o $(OBJDIR)/utils.o

# Executable
TARGET = chat

# Create object directory and compile
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Clean up the build
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean
