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
#include "mailbox.h"
#include <stdlib.h>
#include <stdio.h>


/*..........................................................................*/
void tickTaskA(SSTEvent e) {
	switch (e.sig){
		case INIT_SIG:{
			puts("TaskA INIT_SIG Running...");
			break;
		}
		case TICK_SIG:{
			uint8_t exec = do_sem_down(&(mb.mutex),TICK_TASK_A_PRIO);
			if(exec == OK){
				if(!isEmpty(&mb)){
						printf("TaskA TICK_SIG Running... Get %d from mailbox!\n",get(&mb));
				}
				int msg = 2016;
				put(&mb,msg);
				// SST_INT_LOCK();
				SST_post(TICK_TASK_C_PRIO,TICK_SIG,0);
				SST_post(TICK_TASK_D_PRIO,TICK_SIG,0);
				// SST_INT_UNLOCK();
				do_sem_up(&(mb.mutex));
    		}
			break;
		}
	}
}

void tickTaskB(SSTEvent e) {
	switch (e.sig){
		case INIT_SIG:{
			puts("TaskB INIT_SIG Running...");
			break;
		}
		case TICK_SIG:{
			uint8_t exec = do_sem_down(&(mb.mutex),TICK_TASK_B_PRIO);
			if(exec == OK){
				if(!isEmpty(&mb)){
					printf("TaskB TICK_SIG Running... Get %d from mailbox!\n",get(&mb));
				}
				int msg = 2017;
				put(&mb,msg);
				do_sem_up(&(mb.mutex));
    		}
			break;
		}
	}
}
void tickTaskC(SSTEvent e){
	switch (e.sig){
		case INIT_SIG:{
			puts("TaskC INIT_SIG Running...");
			break;
		}
		case TICK_SIG:{
			uint8_t exec = do_sem_down(&(mb.mutex),TICK_TASK_C_PRIO);
			if(exec == OK){
				if(!isEmpty(&mb)){
					printf("TaskC TICK_SIG Running... Get %d from mailbox!\n",get(&mb));
				}
				int msg = 2018;
				put(&mb,msg);
				do_sem_up(&(mb.mutex));
    		}
			break;
		}
	}
}
void tickTaskD(SSTEvent e){
	switch (e.sig){
		case INIT_SIG:{
			puts("TaskD INIT_SIG Running...");
			break;
		}
		case TICK_SIG:{
			uint8_t exec = do_sem_down(&(mb.mutex),TICK_TASK_D_PRIO);
			if(exec == OK){
				if(!isEmpty(&mb)){
				printf("TaskD TICK_SIG Running... Get %d from mailbox!\n",get(&mb));
				}
				int msg = 2019;
				put(&mb,msg);
				do_sem_up(&(mb.mutex));
    	}
			break;
		}
	}
}
