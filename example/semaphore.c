#include "semaphore.h"
#include <stdlib.h>
#include "sst_exa.h"
#include "sst_port.h"
// #include <util/delay.h>
#include <math.h>

/*https://github.com/shervinshaikh/minix/blob/master/semaphore.c*/
/*http://stackoverflow.com/questions/330793/how-to-initialize-a-struct-in-accordance-with-c-programming-language-standards*/
Semaphore ConstructSemaphore(int8_t c){
	Semaphore sem = (Semaphore){ .counter = c,.tasksWaiting = 0};
	return sem;
}

uint8_t do_sem_down(Semaphore *sem, uintX_t prior){

	if(!sem){
		return NULL_ERROR;
	}

	if(sem->counter > 0){
		sem->counter--;
		return OK;
	}

	sem->tasksWaiting |= (1ULL << (prior-1));  //põe tarefa na "fila"
	return BUSY;

}

uint8_t do_sem_up(Semaphore *sem){

	sem->counter++;
	if(sem->tasksWaiting > 0){ //there is any taskPrior waiting for resources?
		uintX_t p = 0;
		uintX_t taskPrior = sem->tasksWaiting;
		uintX_t iteratorPrior = ITERATORPRIOR;

    while(p == 0){
      p = taskPrior & iteratorPrior;
    	if(p == 0) iteratorPrior >>= 1ULL;
    }
	  sem->tasksWaiting &= ~iteratorPrior;

		p = log(p)/log(2) +1; //calc log base 2 by ln

		SST_INT_LOCK();
		SST_post(p,TICK_SIG,0);
		SST_INT_UNLOCK();
	}

	return OK;
}
//
// void blinkTest(){
// 	uint8_t i =0;
// 	for (i = 0; i < 10; i++)
// 	{
// 		_delay_ms(50);
// 		PORTB |= (1 << PORTB5);
// 		_delay_ms(50);
// 		PORTB &= (~(1 << PORTB5));
//
// 	}
// }
