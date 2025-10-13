#define _POSIX_C_SOURCE 200809L
#include <stdio.h> 
#include <stdint.h>
#include <string.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <inttypes.h> 

int main()
{
    int fd;
    const char filename[] = "test.txt";
    char buf[] = "Hello World";

    // O_TRUNC truncates (clears) the file to zero bytes if it already exists.
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd < 0)
    {
        perror("open failed");
        return 0;
    }

    int writeRes = write(fd, buf, strlen(buf));
    if (writeRes < 0)
    {
        perror("write failed");
        close(fd);
        return 1;
    }
    printf("Wrote %d bytes to %s\n", writeRes, filename);

    // Ensures that all changes are written to disk before using stat().
    // If we don’t close the file, stat() might read outdated information.
    close(fd);

    struct stat sb;
    if (stat(filename, &sb) == -1) 
    {
        perror("stat failed");
        return 1;
    }
    printf("ID of containing device:  [%x,%x]\n", major(sb.st_dev), minor(sb.st_dev));
    printf("File Type: ");
    switch (sb.st_mode & S_IFMT)
    {
        case S_IFBLK: printf("block device"); break;
        case S_IFCHR: printf("character device"); break;
        case S_IFDIR: printf("directory"); break;
        case S_IFIFO: printf("FIFO/pipe"); break;
        case S_IFLNK: printf("symlink"); break;
        case S_IFREG: printf("regular file"); break;
        case S_IFSOCK: printf("socket"); break;
        default: printf("unknown?"); break;
    }

    printf("\nI-node number: %ju\n", (uintmax_t)sb.st_ino);
    printf("sizeof(uintmax_t): %jd\n",sizeof(uintmax_t));
    printf("File size: %jd bytes\n\n", (intmax_t)sb.st_size);

    printf("Last status change:     %s\n", ctime(&sb.st_ctim.tv_sec));
    printf("Last file access:       %s\n", ctime(&sb.st_atim.tv_sec));
    printf("Last file modification: %s\n", ctime(&sb.st_mtim.tv_sec));

    return 0;
}