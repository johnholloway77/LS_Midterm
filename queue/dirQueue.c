#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "./dirQueue.h"


Node *createNode(const char *path){
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        perror("Couldn't allocate node: ");
        return NULL;
    }
    newNode->pathName = strdup(path);
    newNode->next = NULL;

    return newNode;
}

void initQueue(Queue *q){
    q->front = q->rear = NULL;
}

int isEmpty(Queue *q){
    return q->front == NULL;
}

void enqueue(Queue *q, const char *path){
    Node *newNode = createNode(path);
    if(isEmpty(q)){
        q->front = q->rear = newNode;
    } else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

char* dequeue(Queue *q){
    if(isEmpty(q)){
        //perror("Queue empty ");
        return NULL;
    }else{
        Node *temp = q->front;
        char *path = temp->pathName;

        q->front = q->front->next;
        if(q->front == NULL){
            q->rear = NULL;
        }
        free(temp);
        return path;
    }


}
