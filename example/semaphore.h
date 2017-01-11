#include "sst.h"
#include <stdint.h>
#define NULL_ERROR 0
#define BUSY 1
#define OK 2

typedef struct Semaphore_t
{
	int8_t counter;
	uintX_t tasksWaiting;
} Semaphore;


void ConstructSemaphore(int8_t c, Semaphore* sem);
// uint8_t do_sem_init(Semaphore *s);
uint8_t do_sem_down(Semaphore *sem, uintX_t prior);
uint8_t do_sem_up(Semaphore *sem);

extern 	Semaphore s;
