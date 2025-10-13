.PHONY: all run clean

# Default target: build executable
all:
	gcc -Wall -Wextra -O2 -D_POSIX_C_SOURCE=200809L -o fileStat fileStat.c

# Build and run
run: all
	@echo "=== Running fileStat ==="
	@./fileStat

# Clean build file and output file
clean:
	rm -f fileStat test.txt
