/* logservice.h -- definitions for the  log service */
#ifndef LOGSERVICE_H /* prevent multiple inclusion */
#define LOGSERVICE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>

/* key for the queue */
#define KEY ftok("logservice.h", 'a')

/* message structure */ 
#define MSGCHARS 255
/* MSGCHARS is the number of characters in the message!*/
struct msg_buf
{
	long mtype;
	char mtext[MSGCHARS+1]; /* allow it to be a string! */
} message;

/* function prototypes */
int logServiceInit();
/* initialises the log service client, returns a service id */

int logMessage(int serviceId, char* message);
/* logs the message message to the log service serviceID */

int logServiceEnd(int serviceId);
/* shuts down the log service */

#endif /* ifndef LOGSERVICE_H */ 
