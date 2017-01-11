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

#define BLINK_DELAY_MS 2000
#define BLINK_FAST_DELAY_MS 300


/*..........................................................................*/
void tickTaskA(SSTEvent e) {
	switch (e.sig) {
        case INIT_SIG: {
	      //  PORTB |= (1 << PORTB1);
				 puts("TaskA INIT_SIG Running...");
            break;
        }
        case TICK_SIG: {
    		uint8_t exec = do_sem_down(&s,TICK_TASK_A_PRIO);
				if(exec == OK){
					puts("TaskA TICK_SIG Running...");
					// PORTB ^= (1 << PORTB1); //TOOGLE PORTB
					// SST_INT_LOCK();
					SST_post(TICK_TASK_C_PRIO,TICK_SIG,0);
					SST_post(TICK_TASK_D_PRIO,TICK_SIG,0);
					// SST_INT_UNLOCK();
					do_sem_up(&s);
	    	}
			break;
		}
    }
}

void tickTaskB(SSTEvent e) {
	switch (e.sig) {
        case INIT_SIG: {
					puts("TaskB INIT_SIG Running...");
				//  PORTB |= (1 << PORTB2);
            break;
        }
        case TICK_SIG: {
			uint8_t exec = do_sem_down(&s,TICK_TASK_B_PRIO);
			if(exec == OK){
				puts("TaskB TICK_SIG Running...");
				// PORTB ^= (1 << PORTB2); //TOOGLE PORTB
				do_sem_up(&s);
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
			// PORTB |= (1 << PORTB3);
			break;
		}
		case TICK_SIG:{
			uint8_t exec = do_sem_down(&s,TICK_TASK_C_PRIO);
			if(exec == OK){
				puts("TaskC TICK_SIG Running...");
				// PORTB ^= (1 << PORTB3); //TOOGLE PORTB
				do_sem_up(&s);
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
		case TICK_SIG:{
			uint8_t exec = do_sem_down(&s,TICK_TASK_D_PRIO);
			if(exec == OK){
				puts("TaskD TICK_SIG Running...");
				// PORTB ^= (1 << PORTB3); //TOOGLE PORTB
				do_sem_up(&s);
    		}
			break;
		}
	}
}
