/* ch2/fork-child-grandchild.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include	<sys/types.h>
#include	<sys/wait.h>
void err_sys(char *msg);

int main(void)
{
	pid_t	pid;
	
	printf("original process, pid = %d\n", getpid());

	if ((pid = fork()) < 0)

		err_sys("fork error");

	else if (pid == 0) {		/* child */

		printf("child = %d, parent = %d\n", getpid(), getppid()); 
		if ( (pid = fork()) < 0)

			err_sys("fork error");

		else if (pid == 0) {   /* grandchild */
			printf("grandchild = %d, parent = %d\n", getpid(), getppid()); 
			exit(EXIT_SUCCESS);
			}	

		/* child waits for the grandchild */
		if (waitpid(pid, NULL, 0) != pid)	 
			err_sys("waitpid error");
		exit(EXIT_SUCCESS); /* the child can now exit */
				
		}

	/* original process waits for its child to finish */
	if (waitpid(pid, NULL, 0) != pid)	/* wait for first child */
		err_sys("waitpid error");

	/* We're the parent (the original process); we continue executing,
	   knowing that we're not the parent of the other process. */
	exit(0);
}

void err_sys(char *msg)
{
	fprintf(stderr, msg);
	fflush(NULL); /* flush all output streams */	
	exit(EXIT_FAILURE); /* exit abnormally */
}		
