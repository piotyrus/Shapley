#include <stdlib.h>
#include <string.h>

#include "safe_stdlib.h"
#include "graph.h"
#include "queue.h"
#include "macros.h"

static int WHITE = 0;
static int GREY  = 1;
static int BLACK = 2;

static void calculate_edges(Edges *edges, int n, int *occurences)
{
    int i;

    for (i = 0; i < n; ++i)
        occurences[i] = 0;

    for (i = 0; i < edges->m; ++i)
    {
        ++occurences[edges->list[i].v];
        if (edges->list[i].v != edges->list[i].w)
            ++occurences[edges->list[i].w];
    }
}

static void prefix_sum(int *array, int n, int *out)
{
    int sum = 0;
    int i;

    for (i = 0; i < n; ++i)
    {
        out[i] = sum;
        sum += array[i];
    }
    out[n] = sum;
}

static int insert(int *list, double *weights, int *shifts, int idx, int v, 
                  double weight, int *occurences)
{
    int my_idx = shifts[idx + 1] - occurences[idx];
    
    list[my_idx] = v;
    weights[my_idx] = weight;
    --occurences[idx];
    return my_idx;
}

static void init_combined(int *array, int n)
{
    int i;

    for (i = 0; i < n; ++i)
        array[i] = i;
}

static int calculateEdges(Adjacency *adjacency, int *vertices, int n)
{
    int current = 0;
    int i;

    for (i = 0; i < n; ++i)
    {
        int v = vertices[i];
        int e;

        for (e = adjacency->shifts[v]; e != adjacency->shifts[v+1]; ++e)
        {
            ++current;
        }
    }

    return current;

}

static void init_edges(Adjacency *adjacency, int *vertices, int n, int *edges)
{
    int i;
    int current = 0;

    for (i = 0; i < n; ++i)
    {
        int v = vertices[i];
        int e;

        for (e = adjacency->shifts[v]; e != adjacency->shifts[v+1]; ++e)
        {
            edges[current] = e;
            ++current;
        }
    }
}

GraphList *createConnectedSubgraphs(int n, Adjacency *adjacency)
{
    int color[n];
    int *temp;
    GraphList *connected_subgraphs = NULL;
    Queue queue;
    int i;

    for (i = 0; i < n; ++i)
        color[i] = WHITE;

    temp = (int *) safeMalloc(n * sizeof(int));
    initQueue(&queue, n);


    for (i = 0; i < n; ++i)
    {
        if (color[i] == WHITE)
        {
            GraphList *head = (GraphList *) safeMalloc(sizeof(GraphList));

            head->next = connected_subgraphs;
            connected_subgraphs = head;

            head->graph.n = 0;
            push(&queue, i);
            color[i] = GREY;

            while(!empty(&queue))
            {
                int v; 
                int i;

                v = pop_front(&queue);

                temp[head->graph.n++] = v;
                
                for (i = adjacency->shifts[v];
                     i != adjacency->shifts[v + 1]; ++i)
                {
                    int w = adjacency->edges[i];
                    if (color[w] == WHITE)
                    {
                        color[w] = GREY;
                        push(&queue, w);
                    }
                }
                color[v] = BLACK;
            }

            head->graph.vertices = (int *) safeMalloc(head->graph.n * sizeof(int));
            memcpy(head->graph.vertices, temp, head->graph.n * sizeof (int));

            head->graph.m = calculateEdges(adjacency, head->graph.vertices, head->graph.n);
            head->graph.edges = (int *) safeMalloc(head->graph.m * sizeof(int));
            init_edges(adjacency, head->graph.vertices, head->graph.n, head->graph.edges);
        }
    }

    releaseQueue(&queue);
    free(temp);

    return connected_subgraphs;
}

void releaseConnectedSubgraphs(GraphList *connected_subgraphs)
{
    while (connected_subgraphs != NULL)
    {
        GraphList *tmp = connected_subgraphs->next;

        free(connected_subgraphs->graph.vertices);
        free(connected_subgraphs->graph.edges);
        free(connected_subgraphs);

        connected_subgraphs = tmp;
    }
}

static void init_is(int *shifts, int n, int *is)
{
    int v;
    int i;
    int current = 0;

    for (v = 0; v < n; ++v)
        for (i = shifts[v]; i < shifts[v+1]; ++i)
        {
            is[current] = v;
            ++current;
        }
}

static int calculate_virtuals(int *shifts, int n, int mdeg)
{
    int virtuals = 0;
    int v;

    for (v = 0; v < n; ++v)
    {
        int m = shifts[v+1] - shifts[v];

        if (m == 0)
            ++virtuals;
        else
            virtuals += (m + mdeg - 1) / mdeg;
    }

    return virtuals;
}

static int init_virtual_shifts(int *shifts, int n, int mdeg, 
                               int *virtualShifts)
{
    int current_virtual = 0;
    int current_shift = 0;
    int v;

    for (v = 0; v < n; ++v)
    {
        int m = shifts[v+1] - shifts[v];

        do
        {
            int deg = MIN(m, mdeg);
            virtualShifts[current_virtual] = current_shift;
            ++current_virtual;
            current_shift += deg;
            m -= deg;
        } while (m > 0);
    }

    virtualShifts[current_virtual] = current_shift;

    return current_virtual + 1;
}

static int init_virtual_maps(int *shifts, int n, int mdeg,
                             int *virtualMap, int *reverseMap)
{
    int current = 0;
    int v;

    for (v = 0; v < n; ++v)
    {
        int m = shifts[v+1] - shifts[v];

        reverseMap[v] = current;
        do 
        {
            virtualMap[current] = v;
            ++current;
            m -= mdeg;
        } while (m > 0);
    }

    return current;
}


Adjacency *createAdjacency(int n, Edges *edges, int mdeg)
{
    int shiftsNumber = n + 1;
    int *occurences = (int *) safeMalloc(n * sizeof(int));
    int adjacencyNumber;
    int virtualShiftsNumber;
    int i;
    Adjacency *adjacency = (Adjacency *) safeMalloc(sizeof (Adjacency));

    adjacency->verticesNumber = n;
    adjacency->shifts = (int *) safeMalloc(shiftsNumber * sizeof(int));
    calculate_edges(edges, n, occurences);
    prefix_sum(occurences, n, adjacency->shifts);

    adjacencyNumber = adjacency->shifts[n];
    adjacency->edges = (int *) safeMalloc(adjacencyNumber * sizeof (int));
    adjacency->is = (int *) safeMalloc(adjacencyNumber * sizeof (int));
    adjacency->combined = (int *) safeMalloc(adjacencyNumber * sizeof (int));

    adjacency->virtualVerticesNumber = calculate_virtuals(adjacency->shifts, n, mdeg);
    virtualShiftsNumber = adjacency->virtualVerticesNumber + 1;

    adjacency->virtualMap = (int *) safeMalloc(adjacency->virtualVerticesNumber * sizeof (int));
    adjacency->reverseVirtualMap = (int *) safeMalloc(n * sizeof (int));
    adjacency->virtualShifts = (int *) safeMalloc(virtualShiftsNumber * sizeof (int));

    adjacency->weights = (double *) safeMalloc(adjacencyNumber * sizeof (double));

    init_is(adjacency->shifts, n, adjacency->is);
    init_combined(adjacency->combined, adjacencyNumber);

    init_virtual_maps(adjacency->shifts, n, mdeg, adjacency->virtualMap, 
                      adjacency->reverseVirtualMap);

    init_virtual_shifts(adjacency->shifts, n, mdeg, adjacency->virtualShifts);

    for (i = 0; i < edges->m; ++i)
    {
        int v1 = edges->list[i].v;
        int v2 = edges->list[i].w;
        double w = edges->list[i].weight;
        int e1 = insert(adjacency->edges, adjacency->weights, adjacency->shifts,
                        v1, v2, w, occurences);

        if (v1 != v2)
        {
            int e2 = insert(adjacency->edges, adjacency->weights, adjacency->shifts,
                            v2, v1, w, occurences);
            adjacency->combined[e1] = e2;
            adjacency->combined[e2] = e1;
        }
    }

    free(occurences);

    return adjacency;
}

void releaseAdjacency(Adjacency *adjacency)
{
    free(adjacency->shifts);
    free(adjacency->edges);
    free(adjacency->is);
    free(adjacency->combined);
    free(adjacency->virtualMap);
    free(adjacency->reverseVirtualMap);
    free(adjacency->virtualShifts);
    free(adjacency->weights);
    free(adjacency);
}
