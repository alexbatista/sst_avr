#include "sst.h"

typedef struct Semaphore_t
{
	int8_t counter;	
	uintX_t tasksWaiting;
} Semaphore;

Semaphore* ConstructSemaphore();
// uint8_t do_sem_init(Semaphore *s);
uint8_t do_sem_down(Semaphore *s, uintX_t prior);
uint8_t do_sem_up(Semaphore *s);

extern 	Semaphore *s;