#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <stdio.h>
#include "safe_stdlib.h"

void *safeMalloc(size_t size)
{
    void *alloc = malloc(size);

    if (!alloc)
    {
        perror("Error: malloc");
        exit(EXIT_FAILURE);
    }

    return alloc;
}

FILE *safeFopen(const char *path, const char *mode)
{
    FILE *file = fopen(path, mode);

    if (!file)
    {
        perror("Error: fopen");
        exit(EXIT_FAILURE);
    }

    return file;
}

void safeFseek(FILE *stream, long offset, int whence)
{
    if (fseek(stream, offset, whence))
    {
        perror("Error: fseek");
        exit(EXIT_FAILURE);
    }
}

void *safeMmap(void *start, size_t length, int prot , int flags, int fd, off_t offset)
{
    void *alloc = mmap(start, length, prot, flags, fd, offset);

    if (alloc == MAP_FAILED)
    {
        perror("Error: mmap");
        exit(EXIT_FAILURE);
    }

    return alloc;
}

void print_buffer(const char *name, int *buffer, int m, int n)
{
    int j;
    printf("%s\n", name);
    for (j = 0; j < m; ++j)
    {
        int i;
        int *buffer_m = buffer + n * j;

        for (i = 0; i < n - 1; ++i)
            printf("%d ", buffer_m[i]);
        if (n > 0)
            printf("%d\n", buffer_m[n - 1]);
    }
}

void print_time(const char *name, long time)
{
    long time_ms = (time + 500000) / 1000000;
#ifndef NDEBUG
    {
        long minutes = time_ms / 60000;
        double seconds = (time_ms % 60000) * 1e-3;
        int len = strlen(name);
        char buffer[31];

        memset(buffer, ' ', 30);
        buffer[30] = '\0';

        if (len < 31)
            strncpy(buffer, name, len);

        fprintf(stderr, "%s", name);
        while (len < 30)
        {
            len += 1;
            fprintf(stderr, " ");
        }
        fprintf(stderr, "%ldm%.3fs\n", minutes, seconds);
    }
#else
    {
        fprintf(stderr, "%ld\n", time_ms);
    }
#endif
}

