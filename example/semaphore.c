#include "semaphore.h"
#include <stdlib.h>
#include "sst_exa.h"
#include "sst_port.h"

/*https://github.com/shervinshaikh/minix/blob/master/semaphore.c*/

Semaphore ConstructSemaphore(int8_t c){
	Semaphore sem = { .counter = c, .tasksWaiting = 0};
	// sem.tasksWaiting = 0;
	// sem->counter = (int8_t)c;

	return sem;
}

uint8_t do_sem_down(Semaphore *sem, uintX_t prior){

	if(!sem){
		return NULL_ERROR;
	}
	
	if(!sem->counter)
		return NULL_ERROR;
	
	sem->counter--;
	
	if(sem->counter < 0){ //se counter < 0 não há recurso disponível, jogar tarefa na fila de espera
		sem->tasksWaiting |= prior;  //põe tarefa na "fila"
		return BUSY;
	}
	return OK;
}

uint8_t do_sem_up(Semaphore *sem){
	sem->counter++;
	if(sem->counter <= 0){ //there is any taskPrior waiting for resources?
		uintX_t p = 0;
		uintX_t taskPrior = sem->tasksWaiting;
		uintX_t iteratorPrior = ITERATORPRIOR;
		 do{
            p = taskPrior & iteratorPrior;
            iteratorPrior >>= 1;
        }while(p == 0);
        sem->tasksWaiting &= ~iteratorPrior;
		uint8_t pin;
	    SST_ISR_ENTRY(pin, TICK_ISR_PRIO);
		SST_post(p,TICK_SIG,0);
		SST_ISR_EXIT(pin,pin);
	}

	return OK;
}