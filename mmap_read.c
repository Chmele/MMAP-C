#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>

void r_read(int fd, int buffer_size)
{
    char buffer[buffer_size];
    int n;

    while ((n = read(fd, buffer, buffer_size - 1)) > 0)
    {
        buffer[n] = '\0';
    }
}

void m_mmap_private(int fd)
{
    struct stat statbuf;
    fstat(fd, &statbuf);

    char *data = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    munmap(data, statbuf.st_size);
}

int main(int argc, char *argv[])
{
    int opt, buffer_size = 64;

    char *file_names[7] = {
        "files/file1", 
        "files/file32", 
        "files/file1024", 
        "files/file32768",
        "files/file1048576",
        "files/file33554432",
        "files/file1073741824",
    };
    for (int i=0; i<7; i++){
        int fd = open(file_names[i], O_RDONLY);
        clock_t begin = clock();
        r_read(fd, buffer_size);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%f\n", time_spent);
        close(fd);
    }
    for (int i=0; i<7; i++){
        int fd = open(file_names[i], O_RDONLY);
        clock_t begin = clock();
        m_mmap_private(fd);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%f\n", time_spent);
        close(fd);
    }
    return 0;
}