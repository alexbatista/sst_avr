#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

Queue ConstructQueue(int lim) {
    Queue queue = { .limit = lim, .size = 0, .s = {.counter = (int8_t)1}};
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
    printf("Enqueue Starting!! ------------------\n");
    if (pQueue->size == 0) {
        pQueue->head = item;
        pQueue->tail = item;
        printf("Putting the first element to queue: %d\n",pQueue->tail->info);
    } else {
        /*adding item to the end of the queue*/
        pQueue->tail->prev = item;
        pQueue->tail = item;
        printf("Enqueue! Putting element to queue: %d\n",pQueue->tail->info);
    }
    printf("The info in HEAD is: %d\n",pQueue->head->info);
    printf("The info in TAIL is: %d\n",pQueue->tail->info);
    pQueue->size++;

    printf("The size of the queue is now: %d\n\n", pQueue->size);
    printf("Enqueue Ending!! ------------------\n\n");
    return TRUE;
}

NODE *Dequeue(Queue *pQueue) {
    /*the queue is empty or bad param*/
    if(pQueue == NULL || pQueue->size == 0){
      return NULL;
    }
    printf("Dequeue Starting!! ------------------\n");
    printf("The info in HEAD is: %d\n",pQueue->head->info);
    printf("The info in TAIL is: %d\n",pQueue->tail->info);
    NODE *item = pQueue->head;
    // if(pQueue->size > 1){
    pQueue->head = (pQueue->head)->prev;
    // }
    printf("The info in new HEAD is: %d\n",pQueue->head->info);
    printf("The info in new TAIL is: %d\n",pQueue->tail->info);
    pQueue->size--;
    printf("The size of the queue is now: %d. The value of the item dequeue was: %d\n", pQueue->size,item->info);
    printf("Dequeue Ending!! ------------------\n\n");
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
