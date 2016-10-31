/*****************************************************************************
* SST platform-independent implementation
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


/* Public-scope objects ----------------------------------------------------*/
uintX_t SST_currPrio_ = (uintX_t)0xFF;              /* current SST priority */
uintX_t SST_readySet_ = (uintX_t)0;                        /* SST ready-set */

typedef struct TaskCBTag TaskCB;
struct TaskCBTag {
    SSTTask task__;
    SSTEvent *queue__;
    uintX_t end__;
    uintX_t head__;
    uintX_t tail__;
    uintX_t nUsed__;
    uintX_t mask__;
};

/* Local-scope objects -----------------------------------------------------*/
static TaskCB l_taskCB[SST_MAX_PRIO];

/*..........................................................................*/
void SST_task(SSTTask task, uintX_t prio, SSTEvent *queue, uintX_t qlen,
              SSTSignal sig, SSTParam par)
{
    SSTEvent ie;                                    /* initialization event */
    TaskCB *tcb  = &l_taskCB[prio - 1];
    tcb->task__  = task;
    tcb->queue__ = queue;
    tcb->end__   = qlen;
    tcb->head__  = (uintX_t)0;
    tcb->tail__  = (uintX_t)0;
    tcb->nUsed__ = (uintX_t)0;
    tcb->mask__  = (1 << (prio - 1));
    ie.sig = sig;
    ie.par = par;
    tcb->task__(ie);                                 /* initialize the task */
}
/*..........................................................................*/
void SST_run(void) {
    // SST_start();                                              /* start ISRs */

    SST_INT_LOCK();
    SST_currPrio_ = (uintX_t)0;   /* set the priority for the SST idle loop */
    SST_schedule_();                  /* process all events produced so far */
    SST_INT_UNLOCK();

    for (;;) {                                         /* the SST idle loop */
        SST_onIdle();                        /* invoke the on-idle callback */
    }
}
/*..........................................................................*/
uintX_t SST_post(uintX_t prio, SSTSignal sig, SSTParam par) {
    TaskCB *tcb = &l_taskCB[prio - 1];
    SST_INT_LOCK();
    if (tcb->nUsed__ < tcb->end__) {
        tcb->queue__[tcb->head__].sig = sig;/* insert the event at the head */
        tcb->queue__[tcb->head__].par = par;
        if ((++tcb->head__) == tcb->end__) {
            tcb->head__ = (uintX_t)0;                      /* wrap the head */ 
        }
        if ((++tcb->nUsed__) == (uintX_t)1) {           /* the first event? */ //O QUE ISSO SIGNIFICA?
            SST_readySet_ |= tcb->mask__;   /* insert task to the ready set */
            SST_schedule_();            /* check for synchronous preemption */
        }
        SST_INT_UNLOCK();
        return (uintX_t)1;                     /* event successfully posted */
    }
    else {
        SST_INT_UNLOCK();
        return (uintX_t)0;              /* queue full, event posting failed */
    }
}
/*..........................................................................*/
uintX_t SST_mutexLock(uintX_t prioCeiling) {
    uintX_t p;
    SST_INT_LOCK();
    p = SST_currPrio_;               /* the original SST priority to return */
    if (prioCeiling > SST_currPrio_) {
        SST_currPrio_ = prioCeiling;              /* raise the SST priority */
    }
    SST_INT_UNLOCK();
    return p;
}
/*..........................................................................*/
void SST_mutexUnlock(uintX_t orgPrio) {
    SST_INT_LOCK();
    if (orgPrio < SST_currPrio_) {
        SST_currPrio_ = orgPrio;    /* restore the saved priority to unlock */
        SST_schedule_();    /* invoke scheduler after lowering the priority */
    }
    SST_INT_UNLOCK();
}
/*..........................................................................*/
/* NOTE: the SST scheduler is entered and exited with interrupts LOCKED */
void SST_schedule_(void) {
    // static uint8_t const log2Lkup[] = {
    //     0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
    //     5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    //     6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    //     6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    //     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    //     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    //     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    //     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    //     8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    //     8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    //     8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    //     8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    //     8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    //     8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    //     8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    //     8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
    // };
    //  uint8_t pin = SST_currPrio_;               /* save the initial priority */
    // uint8_t p;                                           /*the new priority */
    //                         /* is the new priority higher than the initial? */
    // while ((p = log2Lkup[SST_readySet_]) > pin) {


    uintX_t iteratorPrior = ITERATORPRIOR;

    uintX_t pin = SST_currPrio_;               /* save the initial priority */
    uintX_t p = 0;                             /* the new priority */
    
    if( SST_readySet_ > 0){                     /*there is at least one task*/
        do{
            p = SST_readySet_ & iteratorPrior;
            iteratorPrior >>= 1;
        }while(p == 0);
   
                              /* is the new priority higher than the initial? */
        while (p > pin) {
            TaskCB *tcb  = &l_taskCB[p - 1];
                                              /* get the event out of the queue */
            SSTEvent e = tcb->queue__[tcb->tail__];
            if ((++tcb->tail__) == tcb->end__) {
                tcb->tail__ = (uintX_t)0;
            }
            if ((--tcb->nUsed__) == (uintX_t)0) {/* is the queue becoming empty?*/
                SST_readySet_ &= ~tcb->mask__;     /* remove from the ready set */
            }
            SST_currPrio_ = p;        /* this becomes the current task priority */
            SST_INT_UNLOCK();                          /* unlock the interrupts */

            (*tcb->task__)(e);                             /* call the SST task */

            SST_INT_LOCK();            /* lock the interrupts for the next pass */
            
            do{
                p = SST_readySet_ & iteratorPrior;
                iteratorPrior >>= 1;
            }while(p == 0 || iteratorPrior != 0);
            //ATUALIZANDO O VALOR DE P BASEADO NO NOVO SST_readSet, 
            //visto que é necessário que o SST execute a mais nova tarefa de maior prioridade. 
            //No origial era p[SST_readySet_]
        }

        SST_currPrio_ = pin;                    /* restore the initial priority */
    }
}
