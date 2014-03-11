/* ch2/fork-and-wait.c */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
void childs_play(); 
void err_sys(char *msg);

int main(void)
{
	pid_t	pid;

	if ( (pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) {		/* child */
				childs_play();
				exit(EXIT_SUCCESS);
		 } 

	printf("Created child with pid %d\n",pid);
	/* parent continues concurrently with child */
			
	sleep(4);
	printf("Shoo away!\n");
	/* wait for normal termination of child process */
	if (waitpid(pid, NULL, 0) != pid)		
			err_sys("waitpid error");
	exit(EXIT_SUCCESS);
}

void childs_play()
{
	 sleep(3);
     printf("Hey, I need some money! \n");
	 sleep(1);
}

void err_sys(char *msg)
{
	fprintf(stderr, msg);
	fflush(NULL); /* flush all output streams */	
	exit(EXIT_FAILURE); /* exit abnormally */
}		
