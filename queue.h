#ifndef QUEUE_H
#define QUEUE_H

#include "patient.h"

typedef struct QueueNode {
    Patient data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

// Queue functions
void initQueue(Queue *q);
int isQueueEmpty(Queue *q);
void enqueue(Queue *q, Patient p);
Patient dequeue(Queue *q);

#endif