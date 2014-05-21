#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

int dijkstra(Adjacency *adjacency, int n, int s, double distances[], int nodes[]);

#ifdef __cplusplus
}
#endif

#endif /*__DIJKSTRA_H__*/
