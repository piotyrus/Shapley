#include <cmath>
#include <algorithm>
#include <queue>
#include <stdio.h>
#include "dijkstra.h"

typedef std::pair<double, int> vertex_distance;

int dijkstra(Adjacency *adjacency, int n, int s, double distances[], int nodes[])
{
    static std::priority_queue<vertex_distance, std::vector<vertex_distance>, std::greater<vertex_distance> > my_min_heap;
    bool *visited = new bool[n];
    std::vector<vertex_distance> to_sort;
    std::vector<vertex_distance>::iterator it;
    int i;
    int current = 0;
    int reachable = 0;

    for (i = 0; i < n; ++i)
    {
        visited[i] = false;
        distances[i] = +INFINITY;
    }

    distances[s] = 0.0;
    my_min_heap.push(std::make_pair(distances[s], s));
            


    while (!my_min_heap.empty())
    {
        vertex_distance top = my_min_heap.top();
        int u = top.second;
        double d = top.first;
        int *it;

        my_min_heap.pop();

        if (d <= distances[u])
        {
            ++reachable;
            for (i = adjacency->shifts[u]; i != adjacency->shifts[u + 1]; ++i)
            {
                int v = adjacency->edges[i];
                double cost = adjacency->weights[i];

                if (distances[u] + cost < distances[v])
                {
                    distances[v] = distances[u] + cost;
                    my_min_heap.push(std::make_pair(distances[v], v));
                }
            }
        }
    }

    for (i = 0; i < n; ++i)
        to_sort.push_back(std::make_pair(distances[i], i));

    std::sort(to_sort.begin(), to_sort.end());

    for (it = to_sort.begin(), current = 0; it != to_sort.end(); ++it, ++current)
    {
        nodes[current] = it->second;
        distances[current] = it->first;
        //printf("node %d distance %f\n", nodes[i], distances[nodes[i]]);
    }

    delete [] visited;

    return reachable;
}
