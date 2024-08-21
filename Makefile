# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -Iheader

# Directories
SRCDIR = source
OBJDIR = objects
BINDIR = bin

# Source files
SRC = $(SRCDIR)/chat.c $(SRCDIR)/clients.c $(SRCDIR)/utils.c

# Object files
OBJ = $(OBJDIR)/chat.o $(OBJDIR)/clients.o $(OBJDIR)/utils.o

# Executable
TARGET = $(BINDIR)/chat_app

# Create object directory and compile
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the final executable
$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Clean up the build
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: clean
