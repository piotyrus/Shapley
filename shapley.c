#include "shapley.h"

void compute_shapley(Edges *edges, int n, double shapley[],
                     long *kernel_time, long *summary_time)
{
    int i;

    for (i = 0; i < n; ++i)
        shapley[i] = 0.0;
}
