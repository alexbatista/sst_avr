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
// #include "queue.h"
#include "mailbox.h"
// #include "shared.h"
#include <util/delay.h>
#include <stdlib.h>

#define BLINK_DELAY_MS 2000
#define BLINK_FAST_DELAY_MS 300

/*[1] http://stackoverflow.com/questions/11709929/how-to-initialize-a-pointer-to-a-struct-in-c*/
/*..........................................................................*/
void tickTaskA(SSTEvent e) {
	uint8_t exec = do_sem_down(&(mb.mutex),TICK_TASK_A_PRIO);
	if(exec == OK){
		if(&mb !=NULL){
				PORTB |= get(&mb);
			  _delay_ms(BLINK_DELAY_MS);
		}
		int msg = (~(1 << PORTB5));
		put(&mb,msg);
		do_sem_up(&(mb.mutex));
	}
}

void tickTaskB(SSTEvent e) {
	uint8_t exec = do_sem_down(&(mb.mutex),TICK_TASK_B_PRIO);
	if(exec == OK){
		if(&mb !=NULL){
				PORTB &= get(&mb);
			  _delay_ms(BLINK_DELAY_MS);
		}
		int msg = (1 << PORTB5);
		put(&mb,msg);
		do_sem_up(&(mb.mutex));
	}
}