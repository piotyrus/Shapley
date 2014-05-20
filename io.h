#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include "types.h"

void read_input(FILE *input, Edges *edges);

void write_output(int n, double betweenees[], FILE *output);

#endif  /* __IO_H__ */
