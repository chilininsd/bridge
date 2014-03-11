/* ch2/fork-hello-world.c */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include	<sys/types.h>
void print_message_function( void *ptr ); 
void err_sys(char *msg);

int main(void)
{
	pid_t	pid;
    char *message1 = "Goodbye";
    char *message2 = "World";

	/*printf("\n\nbefore fork\n");	*/

	if ( (pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) {		/* first child */
				print_message_function(message1);
				/*sleep(2);*/
				exit(0);
		 } 
	
	/*printf("Created child with pid %d\n",pid);*/
	/* parent continues and creates another child */
	if ( (pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) {		/* second child */
				print_message_function(message2);
				printf("\n");
				/*sleep(2);*/
				exit(0);
	} 
	/*printf("Created child with pid %d\n",pid);*/
			
	/*sleep(2); 			*/
	exit(0);
}


void print_message_function( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s ", message);
}

void err_sys(char *msg)
{
	fprintf(stderr, msg);
	fflush(NULL); /* flush all output streams */	
	exit(1); /* exit abnormally */
}		
