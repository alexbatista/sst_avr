#include <stdlib.h>
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
        return FALSE;
    }
    // if(pQueue->limit != 0)
    if (pQueue->size >= pQueue->limit) {
        return FALSE;
    }
    /*the queue is empty*/

    // item->prev = NULL;
    if (pQueue->size == 0) {
        pQueue->head = item;
        pQueue->tail = item;

    } else {
        /*adding item to the end of the queue*/
        pQueue->tail->prev = item;
        pQueue->tail = item;
    }
    pQueue->size++;
    return TRUE;
}

NODE *Dequeue(Queue *pQueue) {
    /*the queue is empty or bad param*/
    if (isEmpty(pQueue))
        return NULL;
    NODE *item = pQueue->head;
    pQueue->head = pQueue->head->prev;
    pQueue->size--;
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
