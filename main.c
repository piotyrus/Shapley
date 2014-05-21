#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "safe_stdlib.h"
#include "shapley.h"
#include "function.h"
#include "graph.h"

int number_of_vertices(Edges *edges)
{
    int result = -1;
    int i;
    
    for (i = 0; i < edges->m; ++i)
    {
        int v = edges->list[i].v;
        int w = edges->list[i].w;

        if (v > result)
            result = v;
        if (w > result)
            result = w;
    }

    return result + 1; 
}

int main(int argc, char *argv[])
{
    FILE *input = NULL;
    FILE *output = NULL;
    Edges edges = {0, NULL} ;
    double *shapley = NULL;
    long kernel_time = 0;
    long summary_time = 0;
    int n;
    Adjacency *adjacency;

    input = safeFopen(argv[1], "r");
    output = safeFopen(argv[2], "w");

    read_input(input, &edges);

    n = number_of_vertices(&edges);
    shapley = (double *) safeMalloc(n * sizeof(double));

    adjacency = createAdjacency(n, &edges, n);
    compute_shapley(adjacency, n, shapley, function, &kernel_time, &summary_time);
    
    write_output(n, shapley, output);

    print_time("kernel", kernel_time);
    print_time("summary", summary_time);

    releaseAdjacency(adjacency);
    free(shapley);
    free(edges.list);
    fclose(input);
    fclose(output);

    return 0;
}
