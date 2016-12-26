#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

Queue ConstructQueue() {
    Queue queue = { .head = 0, .tail = 0, .size = 0, .s = {.counter = (int8_t)1}};
    return queue;
}

void DestructQueue(Queue *queue) {
    int pN;
    while (!isEmpty(queue)) {
        pN = Dequeue(queue);
        // free(pN);
    }
    free(queue);
}

int Enqueue(Queue *pQueue, int item) {
    /* Bad parameter */
    if ((pQueue == NULL) || (&item == NULL)) {
      puts("The queue or item is NULL");
      return FALSE;
    }
    // if(pQueue->limit != 0)
    if (pQueue->size >= QUEUE_SIZE) {
      puts("The queue is full");
        return FALSE;
    }
    /*the queue is empty*/
    printf("Enqueue Starting!! ------------------\n");
    if (pQueue->size == 0) {
        // pQueue->elements[pQueue->head] = item;
        pQueue->elements[pQueue->tail] = item;
        printf("Putting the first element to queue: %d\n",pQueue->elements[pQueue->tail]);
    } else {
        /*adding item to the end of the queue*/
        if(pQueue->tail == QUEUE_SIZE-1){
          pQueue->tail = 0;
        }else{
          pQueue->tail++;
        }
        pQueue->elements[pQueue->tail] = item;
        printf("Enqueue! Putting element to queue: %d\n",pQueue->elements[pQueue->tail]);
    }
    printf("The info in HEAD is: %d\n",pQueue->elements[pQueue->head]);
    printf("The info in TAIL is: %d\n",pQueue->elements[pQueue->tail]);
    pQueue->size++;

    printf("The size of the queue is now: %d\n\n", pQueue->size);
    printf("Enqueue Ending!! ------------------\n\n");
    return TRUE;
}

int Dequeue(Queue *pQueue) {
    /*the queue is empty or bad param*/
    if(pQueue == NULL || pQueue->size == 0){
      return -1;
    }
    printf("Dequeue Starting!! ------------------\n");
    printf("The info in HEAD is: %d\n",pQueue->elements[pQueue->head]);
    printf("The info in TAIL is: %d\n",pQueue->elements[pQueue->tail]);
    int info = pQueue->elements[pQueue->head];
    // if(pQueue->size > 1){
    // pQueue->head = (pQueue->head)->prev;
    // }
    if(pQueue->head == QUEUE_SIZE-1){
      pQueue->head = 0;
    }else if(pQueue->size > 1){ //if size of the queue is 1, when the dequeue occurs the head must be in the same place that the tail.
      pQueue->head++;
    }
    pQueue->size--;
    printf("The info in new HEAD is: %d\n",pQueue->elements[pQueue->head]);
    printf("The info in new TAIL is: %d\n",pQueue->elements[pQueue->tail]);
    printf("The size of the queue is now: %d. The value of the item dequeue was: %d\n", pQueue->size,info);
    printf("Dequeue Ending!! ------------------\n\n");
    return info;
}

int isEmpty(Queue *pQueue) {
    if (pQueue == NULL) {
        return TRUE;
    }
    if (pQueue->size == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}
