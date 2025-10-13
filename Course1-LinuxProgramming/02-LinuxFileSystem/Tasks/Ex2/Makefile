.PHONY: all runw runr clean

# Build chương trình
all:
	gcc -Wall -Wextra -O2 -o cmdLineArg cmdLineArg.c

# Chạy ở chế độ ghi (write)
runw: all
	@echo "=== Writing to file ==="
	@./cmdLineArg myfile.txt 12 w "Hello Linux!"
	@echo "\n--- myfile.txt content ---"
	@cat myfile.txt || echo "(no myfile.txt found)"
	@echo ""

# Chạy ở chế độ đọc (read)
runr: all
	@echo "=== Reading from file ==="
	@./cmdLineArg myfile.txt 12 r

# Xóa file build và file dữ liệu
clean:
	rm -f cmdLineArg myfile.txt
