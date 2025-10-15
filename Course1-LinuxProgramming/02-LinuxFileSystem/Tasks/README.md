# File System in Linux
- This section contains three small C programs demonstrating low-level file operations in Linux using POSIX system calls (`open`, `read`, `write`, `lseek`, `stat`, etc.).
- Each exercise illustrates a key concept of how Linux handles files internally.

## Exercise 1 – File Seek and O_APPEND

### Objective

Write a program to:

1. Open a file using the `O_APPEND` flag.

2. Move the file offset to the beginning using `lseek()`.

3. Attempt to write new data and observe the result.

Even though we move the cursor to the beginning of the file with:
```bash
lseek(fd, 0, SEEK_SET);
```
the `O_APPEND` flag **forces every write operation to append data at the end of the file**.
This demonstrates how `O_APPEND` overrides manual cursor positioning.

### Run Instructions
```bash
cd Ex1
make run
```
The program will:
- Create or open `text.txt`.
- Write content twice (old and new).
- Display how `O_APPEND` affects write behavior.
- Finally, print the resulting content of `text.txt` to the terminal.

## Exercise 2 – Command Line File Operations
### Objective

Write a program that takes `command-line arguments` to perform `read/write` operations on files using system calls.

Program syntax:
```bash
./cmdLineArg <filename> <numBytes> <command> [data]
```

### Arguments:
|Argument | Meaning |
|---------|---------|
|`<filename>`| The file to read or write |
|`<numBytes>`| Number of bytes to read/write |
|`<command>` | `r` → read, `w` → write |
|`[data]` | The text to write (required for `w`) |

### Examples:
```bash
./cmdLineArg myfile.txt 12 w "Hello Linux!"
./cmdLineArg myfile.txt 12 r
```
- When using `r`: program reads `<numBytes>` bytes and prints them to screen.
- When using `w`: program writes `<numBytes>` bytes of `[data]` to the file.

### Run Instructions
```bash
cd Ex2
make runw   # write to file
make runr   # read from file
```
This demonstrates how to:

- Use **command-line arguments** in C (`argc`, `argv`).
- Perform **POSIX file I/O** (`open`, `read`, `write`, `close`).
- Manage file permissions and flags (`O_CREAT`, `O_WRONLY`, `O_RDONLY`).

## Exercise 3 – File Metadata with `stat()`
### Objective

Write a program that:

1. Creates a file and writes data into it.

2. Uses `stat()` to retrieve and display detailed file information, including:
- Device ID (major, minor)
- File type (regular, directory, device, etc.)
- Inode number
- File size
- Last access, modification, and status change times

This program demonstrates how **Linux tracks every file through metadata** inside the filesystem.

### Run Instructions
```bash
cd Ex3
make run
```

### Expected output:
```bash
Wrote 11 bytes to test.txt
ID of containing device:  [103,6]
File Type: regular file
I-node number: 10258431
sizeof(uintmax_t): 8
File size: 11 bytes
Last status change:     Tue Oct 14 01:53:25 2025
Last file access:       Tue Oct 14 01:53:25 2025
Last file modification: Tue Oct 14 01:53:25 2025
```

### Key Concepts

- `stat()` reads the file’s metadata stored in the filesystem’s inode.
- Device ID identifies which physical or logical device the file belongs to.
- File type distinguishes between regular files, directories, or device files.
- Timestamps (`st_atim`, `st_mtim`, `st_ctim`) track access, modification, and metadata changes.
- `#define _POSIX_C_SOURCE 200809L` ensures compatibility with modern POSIX definitions required by `struct stat`.