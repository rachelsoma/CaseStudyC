/* logservice.c -- implementation of the log service */
#include "logservice.h"

int logServiceInit()
{
	int id, newLog;

	newLog = logServiceInit();

	if (newLog == -1)
	{
		perror("error");
	}

	return id;
}
/* logs the message message */
int logMessage(int serviceId, char *message)
{
 	int rv;
/*struct message msg;

msg.type=getpid();
strcpy(msg.message,message); */

	return rv;
}
