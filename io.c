#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "safe_stdlib.h"
#include "macros.h"

void read_input(FILE *input, Edges *edges)
{
    int v1;
    int v2;
    int m = 0;

    while (fscanf(input, "%d %d", &v1, &v2) == 2)
        ++m;

    rewind(input);

    edges->m = 0;
    edges->list = (Edge *) safeMalloc(m * sizeof(Edge));

    while (fscanf(input, "%d %d", &v1, &v2) == 2)
    {
        Edge edge = {MIN(v1, v2), MAX(v1, v2)};

        memcpy(&edges->list[edges->m], &edge, sizeof(Edge));
        ++edges->m;
    }
}

void write_output(int n, double betweenees[], FILE *output)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        fprintf(output, "%f\n", betweenees[i]);
    }
}
