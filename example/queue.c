#include <stdlib.h>
#include "queue.h"

Queue *ConstructQueue(int limit) {
    Queue *queue = (Queue*) malloc(sizeof (Queue));
    
    if (queue == NULL) {
        return NULL;
    }
    if (limit <= 0) {
        limit = 65535;
    }
    queue->limit = limit;
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    queue->s = NULL;

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
    item->prev = NULL;
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

NODE * Dequeue(Queue *pQueue) {
    /*the queue is empty or bad param*/
    NODE *item;
    if (isEmpty(pQueue))
        return NULL;
    item = pQueue->head;
    pQueue->head = (pQueue->head)->prev;
    pQueue->size--;
    return item;
}

int isEmpty(Queue* pQueue) {
    if (pQueue == NULL) {
        return FALSE;
    }
    if (pQueue->size == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

//http://stackoverflow.com/questions/11281240/c-sorting-a-queue-of-structures
// void sort(Queue* queue)
// {
//     NODE **pp, *this;

//     if (!queue->head ){
//         fprintf(stderr, "The Queue is empty\n");
//         return;
//        }

//     for(pp = &queue->head; this = *pp; pp = &(*pp)->prev){
//         NODE *other = this->prev;
//         if (!this->prev) break;
//         if (this->prior < other->p) continue;
         
//         ** Now, Swap this (b) and other (c) 
//         ** old situation: @a -> (b) -> (c) -> (d)
//         ** new situation: @a -> (c) -> (b) -> (d) 
        
//         *pp = other;              /* @a  -> (c) */
//         this->prev = other->prev; /* (b) -> (d) */
//         other->prev = this;       /* (c) -> (b) */
//     }
// /* Note: when we get here, "this" will contain the last non-NULL node in the
// ** chain, and can be used to reset the tail-pointer
// */
// return;
// }