#include "sst.h"
#include "semaphore.h"

#define TRUE  1
#define FALSE	0



/* the HEAD of the Queue, hold the amount of node's that are in the queue*/
typedef struct mailBox_t {
	Semaphore mutex;
	int msgAvailable;
	uint8_t size;
} MailBox;

MailBox ConstructMailBox();
void DestructMailBox(MailBox *mailbox);
int put(MailBox *mailbox, int msg);
int get(MailBox *mailbox);
int isEmpty(MailBox *mailbox);

//http://stackoverflow.com/questions/3010647/shared-global-variables-in-c
//http://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files-in-c
extern  MailBox mb;
