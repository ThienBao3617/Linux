.PHONY: all run clean

# Default target: build executable
all:
	gcc -Wall -Wextra -O2 -o fileSeek fileSeek.c

# Build and run
run: all
	@echo "=== Running fileSeek ==="
	@./fileSeek
	@echo "\n--- text.txt content after run ---"
	@cat text.txt || echo "(no text.txt found)"

# Clean build artifacts and output file
clean:
	rm -f fileSeek text.txt
