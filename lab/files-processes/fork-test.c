
/* ch2/fork-test.c */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>

void err_sys(char *msg);

#define MAXNUM 20000

int main(void)
{
	pid_t	pid;
	int i;

	for (i=0; i<MAXNUM; i++) {
		if ( (pid = fork()) < 0)
			err_sys("fork error");
		else if (pid == 0) {		/* ith child */
				sleep(20);
				exit(0);
		 } 
		printf("Created child  number %d with pid %d\n",i,pid);
	}
	exit(0);
}


void err_sys(char *msg)
{
	fprintf(stderr, msg);
	/* or use perror() function */
	if (errno == EAGAIN) 
		fprintf(stderr, "\n Cannot create a task structure\n");
	if (errno == ENOMEM)		
		fprintf(stderr, "\n Not enough memory\n");
	fflush(NULL); /* flush all output streams */	
	exit(1); /* exit abnormally */
}		
