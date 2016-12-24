#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

Queue ConstructQueue(int lim, int sizeSemaphore) {
    Queue queue = { .limit = lim, .size = 0, .s = {.counter = sizeSemaphore}, .head =&(NODE){}, .tail =&(NODE){}}; //info = 0,.toPrior = 0,.prev = malloc(sizeof(NODE))

    return queue;
}

void DestructQueue(Queue *queue) {
    NODE *pN;
    while (!isEmpty(queue)) {
        pN = Dequeue(queue);
        free(pN);
    }
    free(queue);
}

int Enqueue(Queue *pQueue, NODE *item) {
    /* Bad parameter */
    if ((pQueue == NULL) || (item == NULL)) {
      puts("The queue or item is NULL");
      return FALSE;
    }
    // if(pQueue->limit != 0)
    if (pQueue->size >= pQueue->limit) {
      puts("The queue is full");
        return FALSE;
    }
    /*the queue is empty*/

    if (pQueue->size == 0) {
        pQueue->head = item;
        pQueue->tail = item;
        printf("Enqueue! Putting the first element to queue: %d\n",pQueue->tail->info);
    } else {
        /*adding item to the end of the queue*/
        pQueue->tail->prev = item;
        pQueue->tail = item;
        printf("Enqueue! Putting element to queue: %d\n",pQueue->tail->info);
    }
    pQueue->size++;
    printf("The size of the queue is now: %d\n", pQueue->size);
    return TRUE;
}

NODE *Dequeue(Queue *pQueue) {
    /*the queue is empty or bad param*/
    if (isEmpty(pQueue))
        return NULL;
    NODE *item = pQueue->head;
    pQueue->head = (pQueue->head)->prev;
    pQueue->size--;
    printf("Dequeue! The size of the queue is now: %d. The value of the item dequeue was: %d\n", pQueue->size,item->info);
    return item;
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
