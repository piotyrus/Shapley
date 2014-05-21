#ifndef __SHAPLEY_H__
#define __SHAPLEY_H__

#include "types.h"

void compute_shapley(Adjacency *adjacency, int n, double shapley[],
                     double (*function)(double),
                     long *kernel_time, long *summary_time);

#endif /*__SHAPLEY_H__*/
