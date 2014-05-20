#ifndef __SHAPLEY_H__
#define __SHAPLEY_H__

#include "types.h"

void compute_shapley(Edges *edges, int n, double shapley[],
                     long *kernel_time, long *summary_time);

#endif /*__SHAPLEY_H__*/
