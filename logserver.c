/* logserver.c -- implementation of the log server */
#include <signal.h>
#include "logservice.h"
#include "logservice.c"

extern int errno;

#define MAX_LINE 4096
#define MAX_WORDS MAX_LINE / 2
/* a line can have at most MAX_LINE/2 words to account for spaces */
void closeQueue();

int msgqid, rc = 0;

int main()
{
	char line[MAX_LINE], *words[MAX_WORDS];
	int stop = 0, nwords = 0;
	
	int done;
	

	msgqid = msgget(KEY, 0666 | IPC_CREAT | IPC_EXCL);
	if (msgqid < 0)
	{
		perror(strerror(errno));
		printf("failed to create message queue with msgqid = %d\n", msgqid);
		return 1;
	}
	printf("message queue %d created\n", msgqid);

	
	while (1){	
		printf("WS C CLI $ ");
		if (NULL == fgets(line, MAX_LINE, stdin))
		{
			return 0;
		}

		// execvp(launch_server.sh, NULL);
		
		// message to send
		message.mtype = 1;									 // set the type of message
		sprintf(message.mtext, "%s\n", line); /* setting the right time format by means of ctime() */

		// send the message to queue
		rc = msgsnd(msgqid, &message, sizeof(message.mtext), 0); // the last param can be: 0, IPC_NOWAIT, MSG_NOERROR, or IPC_NOWAIT|MSG_NOERROR.
		if (rc < 0)
		{
			perror(strerror(errno));
			printf("msgsnd failed, rc = %d\n", rc);
			return 1;
		}

		// read the message from queue
		rc = msgrcv(msgqid, &message, sizeof(message.mtext), 0, 0);
		if (rc < 0)
		{
			perror(strerror(errno));
			printf("msgrcv failed, rc=%d\n", rc);
			return 1;
		}
		printf("received message %li : %s\n", message.mtype, message.mtext);
		// remove the queue
		signal(SIGINT, closeQueue);
	} 
	return 0;
}
void closeQueue(){
	
			rc = msgctl(msgqid, IPC_RMID, NULL);
			if (rc < 0)
			{
				perror(strerror(errno));
				printf("msgctl (return queue) failed, rc=%d\n", rc);		
			}		
	printf("\n message queue %d deleted\n", msgqid);
}
