#include "sst.h"
#include "semaphore.h"

#define TRUE  1
#define FALSE	0


/* a link in the queue, holds the info and point to the next Node*/
// typedef struct {
//     uintX_t info;
// } DATA;

typedef struct Node_t {
    // DATA data;
    // uintX_t toPrior; //for what task this info goes?
    uint32_t info;
    struct Node_t *prev;
} NODE;

/* the HEAD of the Queue, hold the amount of node's that are in the queue*/
typedef struct Queue {
	Semaphore s;
    NODE *head;
    NODE *tail;
    int size;
    int limit;
} Queue;

Queue ConstructQueue(int limit, int sizeSemaphore);
void DestructQueue(Queue *queue);
int Enqueue(Queue *pQueue, NODE *item);
NODE *Dequeue(Queue *pQueue);
int isEmpty(Queue *pQueue);

//http://stackoverflow.com/questions/3010647/shared-global-variables-in-c
//http://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files-in-c
extern  Queue pQ;
