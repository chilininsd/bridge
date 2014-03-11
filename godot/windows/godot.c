#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <windows.h>

#define CHILD_PROC_TERMINATION_CODE 99
#define PROC_TERMINATION_CODE 127

int pid; /* child process id */
HANDLE * processes;
STARTUPINFO * startupInfos;
PROCESS_INFORMATION * processInfos;
int numProcessors;

void alarm(int *pNumSecs);
DWORD WINAPI AlarmRun(LPVOID threadData);
void OnAlarm(int signo);
void error(char *msg);
void doWork();
void initProcessArrays();

int main(int argc, char *argv[])
{
	int sec=10; /* default timeout */ 
	int status;
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	numProcessors = info.dwNumberOfProcessors;
	int parentPid = GetCurrentProcessId();

	processes = (HANDLE*)malloc(sizeof(HANDLE)*numProcessors);
	startupInfos = (STARTUPINFO*)malloc(sizeof(STARTUPINFO)*numProcessors);
	processInfos = (PROCESS_INFORMATION*)malloc(sizeof(PROCESS_INFORMATION)*numProcessors);
	initProcessArrays();

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

	signal(SIGINT, OnAlarm);
	alarm(&sec);

	printf("original process, pid = %d\n", GetCurrentProcessId());

	int i;
	for (i = 0; i < numProcessors; i++)
	{
		// if ((pid=fork()) == 0)
		// {
		// 	printf("%dth child, pid = %d, parent = %d\n", i, GetCurrentProcessId(), parentPid);
		// 	doWork();	
		// } 
		//else 
		//{
		//	processes[i] = pid;
		//}
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

static void OnAlarm(int signo) /* kill child process when alarm arives */
{
	//printf("\nRecvd alarm signal!\n\n");
	//int i;
	//for (i = 0; i < numProcessors; i++)
	//{
	//	TerminateProcess(hChildProc, CHILD_PROC_TERMINATION_CODE);
	//	kill(processes[i], SIGKILL);
	//}
}

void error(char *msg)
{
	fprintf(stderr, "%s", msg);
	fprintf(stderr,"\n");
	ExitProcess(PROC_TERMINATION_CODE);
}

void doWork()
{
	srand(GetCurrentProcessId());
	for(;;)
	{
		int i, numInRange = 0;
		for (i = 0; i < 1000000000; i++)
		{
			int num = rand();
			if (90 <= num && num <= 110)
			{
				printf("Process %d count = %d\n", GetCurrentProcessId(), ++numInRange);
			}
		}
		Sleep(10000);
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

void initProcessArrays()
{
	int i;
	for (i = 0; i < numProcessors; i++)
	{
		STARTUPINFO si = startupInfos[i];
		PROCESS_INFORMATION pi = processInfos[i];
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
	}
}

DWORD WINAPI AlarmRun(LPVOID threadData)
{
	int numSecs = *((int *)threadData);
	Sleep(1000 * numSecs);
	raise(SIGINT);

	ExitThread(0);
}
