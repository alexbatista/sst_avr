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
// #include "shared.h"
#include <util/delay.h>
#include <stdlib.h>

#define BLINK_DELAY_MS 2000
#define BLINK_FAST_DELAY_MS 300


/*..........................................................................*/
void tickTaskA(SSTEvent e) {
	uint8_t exec = do_sem_down(&s,TICK_TASK_A_PRIO);
	if(exec == OK){
		// NODE *n = Dequeue(pQ);
		// if(n != NULL){
			// PORTB |= n->info;
		 //  _delay_ms(BLINK_DELAY_MS);
	  // }
		PORTB |= (1 << PORTB5); //teste
		_delay_ms(BLINK_DELAY_MS);//teste
		// NODE *node = malloc(sizeof(NODE));
		// node->info = (~(1 << PORTB5));
		// node->toPrior = TICK_TASK_B_PRIO;
		// Enqueue(pQ,node);
		do_sem_up(&s);
	}
}

void tickTaskB(SSTEvent e) {
	uint8_t exec = do_sem_down(&s,TICK_TASK_B_PRIO);
	if(exec == OK){
		// NODE *n = Dequeue(pQ);
		// if(n != NULL){
			// PORTB &= n->info;
		 //  _delay_ms(BLINK_DELAY_MS);
		// }
		PORTB &= (~(1 << PORTB5));
		_delay_ms(BLINK_DELAY_MS);
		// NODE *node = malloc(sizeof(NODE));
		// node->info = (1 << PORTB5);
		// node->toPrior = TICK_TASK_A_PRIO;
		// Enqueue(pQ,node);
		do_sem_up(&s);
	}
}