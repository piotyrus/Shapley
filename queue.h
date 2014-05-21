#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>

typedef struct Queue {
    int begin;
    int end;
    int n;
    int *list;
} Queue;


void initQueue(Queue *queue, int n);

void releaseQueue(Queue *queue);

void push(Queue *queue, int elem);

int pop_front(Queue *queue);

int pop_back(Queue *queue);

bool empty(Queue *queue);

#endif /*__QUEUE_H__*/
