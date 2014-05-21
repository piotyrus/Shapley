#ifndef __GRAPH_H__ 
#define __GRAPH_H__ 

#include "types.h"

typedef struct Stack {
    int n;
    int *list;
} Stack;


Adjacency *createAdjacency(int n, Edges *edges, int mdeg);

void releaseAdjacency(Adjacency *adjacency);

GraphList *createConnectedSubgraphs(int n, Adjacency *adjacency);

void releaseConnectedSubgraphs(GraphList *connected_subgraphs);

#endif /* __GRAPH_H__ */
