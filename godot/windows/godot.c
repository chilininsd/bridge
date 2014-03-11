#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <sys/types.h>
#include <signal.h>
#include <windows.h>


int pid; /* child process id */
int * pids;

static void onalarm(int signo);
void error(char *msg);
void doWork();

int main(int argc, char *argv[])
{
	int sec=10; /* default timeout */ 
	int status;
	int numProcessors = sysconf(_SC_NPROCESSORS_CONF);
	pids = (int*)malloc(sizeof(int)*numProcessors);

	if (argc > 1 && argc < 3) 
	{
		sec = atoi(argv[1]);
		if (sec == 0)
		{
			error("Usage: godot <alarm interval as an integer>\n");
		}
	} 
	else 
	{
		error("Usage: godot <alarm interval>\n");
	}

	// signal(SIGALRM, onalarm);
	alarm(&sec);

	printf("original process, pid = %d\n", getpid());

	int i;
	for (i = 0; i < numProcessors; i++)
	{
		// if ((pid=fork()) == 0)
		// {
		// 	printf("%dth child, pid = %d, parent = %d\n", i, getpid(), getppid());
		// 	doWork();	
		// } 
		else 
		{
			pids[i] = pid;
		}
	}
	
	int j;
	for (j = 0; j < numProcessors; j++)
	{
		// waitpid(pids[j], &status, 0);
		// if (WIFSIGNALED(status))
		// {
		// 	printf("pid = %d %dth child killed with signal %d (Killed) \n", pids[j], j, WTERMSIG(status));	
		// }
	}

	exit(EXIT_SUCCESS);
}

static void onalarm(int signo) /* kill child process when alarm arives */
{
	printf("\nRecvd alarm signal!\n\n");
	int i;
	for (i = 0; i < sysconf(_SC_NPROCESSORS_CONF); i++)
	{
		kill(pids[i], SIGKILL);	
	}
}

void error(char *msg)
{
	fprintf(stderr, "%s", msg);
	fprintf(stderr,"\n");
	exit(EX_SOFTWARE);
}

void doWork()
{
	srand(getpid());
	for(;;)
	{
		int i, numInRange = 0;
		for (i = 0; i < 1000000000; i++)
		{
			int num = rand();
			if (90 <= num && num <= 110)
			{
				printf("Process %d count = %d\n", getpid(), ++numInRange);
			}
		}
		sleep(10);
	}
}

void alarm(int *pNumSecs)
{
	LPHANDLE phThread;
	DWORD dwThreadID;

	phThread = CreateThread(
			NULL,							// Security Descriptor (handle not inheritable)
			0,								// initial stack size (default)
			AlarmRun,					// thread function
			pNumSecs,					// thread argument
			0,								// creation option (run immediately)
			&dwThreadID					// thread identifier
	);
		
	if (! phThread) {
		fprintf(stderr, "Unable to create alarm thread.\n");
		ExitProcess(1);
	}
}
