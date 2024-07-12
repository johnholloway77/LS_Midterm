#ifndef DIRQUEUE_H
#define DIRQUEUE_H

// Node structure
typedef struct Node {
  char *pathName;
  struct Node *next;
} Node;

// Queue structure
typedef struct Queue {
  Node *front;
  Node *rear;
} Queue;

Node *createNode(const char *path);

void initQueue(Queue *q);

int isEmpty(Queue *q);

void enqueue(Queue *q, const char *path);

char *dequeue(Queue *q);

#endif // DIRQUEUE_H
