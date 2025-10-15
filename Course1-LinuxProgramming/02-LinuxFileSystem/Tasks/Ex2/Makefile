.PHONY: all runw runr clean

# Default target: build executable
all:
	gcc -Wall -Wextra -O2 -o cmdLineArg cmdLineArg.c

# Run at write mode
runw: all
	@echo "=== Writing to file ==="
	@./cmdLineArg myfile.txt 12 w "Hello Linux!"
	@echo "\n--- myfile.txt content ---"
	@cat myfile.txt || echo "(no myfile.txt found)"
	@echo ""

# Run at read mode
runr: all
	@echo "=== Reading from file ==="
	@./cmdLineArg myfile.txt 12 r

# Clean build file and output file
clean:
	rm -f cmdLineArg myfile.txt
