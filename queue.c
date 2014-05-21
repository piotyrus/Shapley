#include "queue.h"
#include "safe_stdlib.h"


void initQueue(Queue *queue, int n){
    queue->begin = 0;
    queue->end = 0;
    queue->n = n + 1;
    queue->list = (int *) safeMalloc(queue->n * sizeof (int));
}

void releaseQueue(Queue *queue){
    free(queue->list);
}

void push(Queue *queue, int elem){
    queue->list[queue->end] = elem;
    queue->end = (queue->end + 1) % queue->n;
}

int pop_front(Queue *queue){
    int elem = queue->list[queue->begin];
    queue->begin = (queue->begin + 1) % queue->n;
    return elem;
}

int pop_back(Queue *queue){
    queue->end = (queue->end - 1 + queue->n) % queue->n;
    return queue->list[queue->end];
}

bool empty(Queue *queue){
    return queue->begin == queue->end;
}
