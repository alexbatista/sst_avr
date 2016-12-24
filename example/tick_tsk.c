/*****************************************************************************
* Product: SST example, 80x86, Turbo C++ 1.01
*
* Copyright (C) 2006 Miro Samek and Robert Ward. All rights reserved.
*
* This software may be distributed and modified under the terms of the GNU
* General Public License version 2 (GPL) as published by the Free Software
* Foundation and appearing in the file GPL.TXT included in the packaging of
* this file. Please note that GPL Section 2[b] requires that all works based
* on this software must also be made publicly available under the terms of
* the GPL ("Copyleft").
*
* Contact information:
* Email:    miro@quantum-leaps.com
* Internet: www.quantum-leaps.com
*****************************************************************************/
#include "sst_port.h"
#include "sst_exa.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>


/*..........................................................................*/
void tickTaskA(SSTEvent e) {
	switch (e.sig) {
        case INIT_SIG: {
			puts("TaskA INIT_SIG Running...");
            break;
        }
        case TICK_SIG: {
    		uint8_t exec = do_sem_down(&(pQ.s),TICK_TASK_A_PRIO);
				if(exec == OK){
					NODE *nA = Dequeue(&pQ);
					if(nA !=NULL){
						printf("TaskA TICK_SIG Running ...Get %d information from Queue.\n",nA->info);
						printf("The size of the Queue is now: %d.\n",pQ.size);
					}
					NODE node1 = {.info = 300,.prev=&(NODE){}}; //[1]
					NODE node2 = {.info = 400,.prev=&(NODE){}}; //[1]
					NODE node3 = {.info = 500,.prev=&(NODE){}}; //[1]
					NODE node4 = {.info = 600,.prev=&(NODE){}}; //[1]
					Enqueue(&pQ,&node1);
					Enqueue(&pQ,&node2);
					Enqueue(&pQ,&node3);
					Enqueue(&pQ,&node4);
					SST_INT_LOCK();
					SST_post(TICK_TASK_C_PRIO,TICK_SIG,0);
					SST_post(TICK_TASK_D_PRIO,TICK_SIG,0);
					SST_INT_UNLOCK();
					do_sem_up(&(pQ.s));
    		}
			break;
		}
    }
}

void tickTaskB(SSTEvent e) {
	switch (e.sig) {
        case INIT_SIG: {
			puts("TaskB INIT_SIG Running...");
            break;
        }
        case TICK_SIG: {
			uint8_t exec = do_sem_down(&(pQ.s),TICK_TASK_B_PRIO);
				if(exec == OK){
					NODE *nB = Dequeue(&pQ);
					if(nB !=NULL){
							printf("TaskB TICK_SIG Running ...Get %d information from Queue.\n",nB->info);
							printf("The size of the Queue is now: %d.\n",pQ.size);
					}
					// NODE nodeB = {.info = 2013, .toPrior = TICK_TASK_C_PRIO,.prev=&(NODE){}}; //[1]
					// Enqueue(&pQ,&nodeB);
					do_sem_up(&(pQ.s));
				}
			break;
    	}
    }
}
void tickTaskC(SSTEvent e){
	uint8_t i = 0;
	switch (e.sig){
		case INIT_SIG:{
			puts("TaskC INIT_SIG Running...");
			break;
		}
		case TICK_SIG: {
			uint8_t exec = do_sem_down(&(pQ.s),TICK_TASK_C_PRIO);
				if(exec == OK){
					NODE *nC = Dequeue(&pQ);
					if(nC !=NULL){
							printf("TaskC TICK_SIG Running ...Get %d information from Queue.\n",nC->info);
							printf("The size of the Queue is now: %d.\n",pQ.size);
					}
					// NODE nodeC = {.info = 2014, .toPrior = TICK_TASK_D_PRIO,.prev=&(NODE){}}; //[1]
					// Enqueue(&pQ,&nodeC);
					do_sem_up(&(pQ.s));
				}
			break;
    	}
	}
}
void tickTaskD(SSTEvent e){
	uint8_t i = 0;
	switch (e.sig){
		case INIT_SIG:{
			puts("TaskD INIT_SIG Running...");
			// PORTB |= (1 << PORTB3);
			break;
		}
		case TICK_SIG: {
			uint8_t exec = do_sem_down(&(pQ.s),TICK_TASK_D_PRIO);
				if(exec == OK){
					NODE *nD = Dequeue(&pQ);
					if(nD !=NULL){
							printf("TaskD TICK_SIG Running ...Get %d information from Queue.\n",nD->info);
							printf("The size of the Queue is now: %d.\n",pQ.size);
					}
					// NODE nodeD = {.info = 2015, .toPrior = TICK_TASK_A_PRIO,.prev=&(NODE){}}; //[1]
					// Enqueue(&pQ,&nodeD);
					do_sem_up(&(pQ.s));
				}
			break;
    	}
	}
}
