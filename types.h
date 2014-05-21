#ifndef __TYPES__H__ 
#define __TYPES__H__ 

typedef struct {
    int v;
    int w;
    double weight;
} Edge;

typedef struct {
    int m;
    Edge *list;
} Edges;

typedef struct {
    int verticesNumber;
    int virtualVerticesNumber;
    int *shifts;
    int *edges;
    int *is;
    int *combined;
    int *virtualMap;
    int *reverseVirtualMap;
    int *virtualShifts;
    double *weights;
} Adjacency;

typedef struct {
    int n;
    int m;
    int *vertices;
    int *virtualVertices;
    int *edges;
} Graph;

struct GraphList;

typedef struct GraphList {
    Graph graph;
    struct GraphList *next;
} GraphList;



#endif /* __TYPES__H__ */
