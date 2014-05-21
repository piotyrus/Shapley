#include <math.h>
#include "shapley.h"
#include "dijkstra.h"
#include "safe_stdlib.h"

const double EPSILON = 1.0E-5;

void compute_shapley(Adjacency *adjacency, int n, double shapley[],
                     double (*function)(double),
                     long *kernel_time, long *summary_time)
{
    int i;
    int s;
    double *distances;
    int *nodes;

    distances = (double *) safeMalloc(n * sizeof(double));
    nodes = (int *) safeMalloc(n * sizeof(int));

    for (i = 0; i < n; ++i)
        shapley[i] = 0.0;

    //print_distances("weights", adjacency->weights, 1, adjacency->shifts[n]);

    for (s = 0; s < n; ++s)
    {
        int index;
        double currSV;
        double prevSV;
        double sum = 0.0;
        double prevDistance = -1.0;

        if (s % 1000 == 0)
            printf("progress %d n = %d\n", s, n);

        dijkstra(adjacency, n, s, distances, nodes);

        //print_buffer("nodes", nodes, 1, n);

        //print_distances("distances", distances, 1, reachable);

        for (index = n - 1; index > 0; --index)
        {
            if (distances[index] == prevDistance || fabs(prevDistance - distances[index]) < EPSILON)
                currSV = prevSV;
            else
                currSV = function(distances[index]) / (1.0 + index) - sum;

            shapley[nodes[index]] += currSV; 
            sum += function(distances[index]) / (index * (1.0 + index));

            prevDistance = distances[index];
            prevSV = currSV;
        }

        shapley[s] += function(0.0) - sum;
    }

    free(distances);
    free(nodes);
}
