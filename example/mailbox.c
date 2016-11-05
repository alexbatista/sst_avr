#include <stdlib.h>
#include "mailbox.h"

MailBox ConstructMailBox() {
    MailBox mailbox = {.msgAvailable = 0,.size = 0, .mutex = {.counter = 1, .tasksWaiting = 0}};

    return mailbox;
}

void DestructMailBox(MailBox *mailbox) {
    while (!isEmpty(mailbox)) {
        get(mailbox);
    }
    free(mailbox);
}

int put(MailBox *mailbox, int msg) {
    /* Bad parameter */
    if ((mailbox == NULL) || (&msg == NULL)) {
        return FALSE;
    }

    if (mailbox->size >= 1) {
        return FALSE;
    }

    //MailBox is empty
    if (mailbox->size == 0) {
        mailbox->msgAvailable = msg;
    	mailbox->size++;
    }
    return TRUE;
}

int get(MailBox *mailbox) {
	int msg = 0;
    if (mailbox->size <= 0)
        return NULL;
   
    mailbox->size--;
    msg = mailbox->msgAvailable;
    mailbox->msgAvailable = NULL;
	return msg;	
}

int isEmpty(MailBox *mailbox) {
    if (mailbox == NULL) {
        return FALSE;
    }
    if (mailbox->size == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}