#include "sst.h"

#define TRUE  1
#define FALSE	0

// #ifndef uintX_t
// 	#if nTasks == 8
// 	    typedef uint8_t uintX_t;
// 	#elif nTasks == 16
// 	    typedef uint16_t uintX_t;
// 	#elif nTasks == 32
// 	    typedef uint32_t uintX_t;
// 	#elif nTasks == 64
// 	    typedef uint64_t uintX_t;
// 	#endif
// #endif

/* a link in the queue, holds the info and point to the next Node*/
typedef struct {
    int info;
} DATA;

typedef struct Node_t {
    DATA data;
    SSTTask task;
    struct Node_t *prev;
} NODE;

/* the HEAD of the Queue, hold the amount of node's that are in the queue*/
typedef struct Queue {
    NODE *head;
    NODE *tail;
    int size;
    int limit;
} Queue;

Queue *ConstructQueue(int limit);
void DestructQueue(Queue *queue);
int Enqueue(Queue *pQueue, NODE *item);
NODE *Dequeue(Queue *pQueue);
int isEmpty(Queue* pQueue);