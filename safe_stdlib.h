#ifndef __SAFE_STDLIB_H__
#define __SAFE_STDLIB_H__

#include <stdlib.h>
#include <stdio.h>

void *safeMalloc(size_t size);

FILE *safeFopen(const char *path, const char *mode);

void safeFseek(FILE *stream, long offset, int whence);

void *safeMmap(void *start, size_t length, int prot , int flags, int fd, off_t offset);

void print_buffer(const char *name, int *buffer, int m, int n);

void print_distances(const char *name, double *buffer, int m, int n);

void print_time(const char *name, long time);

#endif /*__SAFE_STDLIB_H__*/
