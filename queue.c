#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

int isQueueEmpty(Queue *q) {
    return (q->front == NULL);
}

void enqueue(Queue *q, Patient p) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = p;
    temp->next = NULL;
    if (!q->rear) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

Patient dequeue(Queue *q) {
    Patient p;
    if (isQueueEmpty(q)) {
        p.id = -1;
        return p;
    }
    QueueNode* temp = q->front;
    p = temp->data;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return p;
}