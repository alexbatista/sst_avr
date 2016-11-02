#include "semaphore.h"
#include <stdlib.h>
#include "sst_exa.h"
#include "sst_port.h"

/*https://github.com/shervinshaikh/minix/blob/master/semaphore.c*/

Semaphore* ConstructSemaphore(){
	Semaphore *s = (Semaphore*)malloc(sizeof(Semaphore));
	s->tasksWaiting = 0;
	s->counter = (int8_t)1;

	return s;
}

uint8_t do_sem_down(Semaphore *s, uintX_t prior){

	if(s == NULL){
		return 0;
	}
	
	s->counter--;
	if(s->counter < 0){ //se counter < 0 não há recurso disponível, jogar tarefa na fila de espera
		s->tasksWaiting |= prior;  //põe tarefa na "fila"
		return 0;
	}
	return 1;
}

uint8_t do_sem_up(Semaphore *s){
	s->counter++;
	if(s->counter <= 0){ //there is any taskPrior waiting for resources?
		uintX_t p = 0;
		uintX_t taskPrior = s->tasksWaiting;
		uintX_t iteratorPrior = ITERATORPRIOR;
		 do{
            p = taskPrior & iteratorPrior;
            iteratorPrior >>= 1;
        }while(p == 0);
        s->tasksWaiting &= ~iteratorPrior;
		uint8_t pin;
	    SST_ISR_ENTRY(pin, TICK_ISR_PRIO);
		SST_post(p,TICK_SIG,0);
		SST_ISR_EXIT(pin,pin);
	}

	return 1;
}