#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <strsafe.h>
#include <signal.h>
#include <windows.h>

#define CHILD_PROC_TERMINATION_CODE 99
#define PROC_TERMINATION_CODE 127
#define BUFF_SIZE 512

int pid; /* child process id */
HANDLE * processes;
STARTUPINFO * startupInfos;
PROCESS_INFORMATION * processInfos;
int numProcessors;

void alarm(int *pNumSecs);
DWORD WINAPI AlarmRun(LPVOID threadData);
void OnAlarm(int signo);
void doWork();
void ErrorExit(LPTSTR lpszFunction);

int main(int argc, char *argv[])
{
	int sec;
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	numProcessors = info.dwNumberOfProcessors;

	/*
	* Maintain three arrays instead of one.
	*/
	processes = (HANDLE*)malloc(sizeof(HANDLE)*numProcessors);
	startupInfos = (STARTUPINFO*)malloc(sizeof(STARTUPINFO)*numProcessors);
	processInfos = (PROCESS_INFORMATION*)malloc(sizeof(PROCESS_INFORMATION)*numProcessors);
	
	if (argc == 2) 
	{
		sec = atoi(argv[1]);
		if (sec == 0)
		{
			ErrorExit(TEXT("Usage: godot <alarm interval as an integer>\n"));
		}
	}
	else if (argc == 3 && argv[2][0] == 'w')
	{
		/*
		* if this program is ran by a child, it passes the "work" flag and is brought here.
		*/
		doWork();
	}
	else
	{
		ErrorExit(TEXT("Usage: godot <alarm interval>\n"));
	}

	/*
	* Set up signal handler and alarm
	*/
	signal(SIGINT, OnAlarm);
	alarm(&sec);

	printf("original process, pid = %d\n", GetCurrentProcessId());

	char str[BUFF_SIZE];
	sprintf_s(str, BUFF_SIZE, "%s 5 w", argv[0]);
	int i = 0;
	for (i = 0; i < numProcessors; i++)
	{
		/*
		* Create all the children...my precious little kiddies.
		*/
		STARTUPINFO si = startupInfos[i];
		PROCESS_INFORMATION pi = processInfos[i];
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		if (!CreateProcess(NULL, str, NULL, NULL, FALSE, 0, NULL, NULL,&si,&pi))
		{
			ErrorExit(TEXT("Failed to start process"));
		}
		processInfos[i] = pi;
		processes[i] = pi.hProcess;
		printf("%dth child, pid = %d, parent = %d\n", i, pi.dwProcessId, GetCurrentProcessId());
	}
	
	/*
	* Wait for all of the processes!!
	*/
	WaitForMultipleObjects(numProcessors, processes, TRUE, INFINITE);

	int j;
	for (j = 0; j < numProcessors; j++)
	{
		/*
		* Close up the handles because we're done with the processes and get their exit code
		*/
		int status;
		PROCESS_INFORMATION pi = processInfos[j];
		GetExitCodeProcess(pi.hProcess, &status);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		printf("pid = %d %dth child killed with signal %d (Killed) \n", pi.dwProcessId, j, status);	
	}

	ExitProcess(EXIT_SUCCESS);
}

/**
* Upon receiving the signal, kill all the children like a Black-tailed prairie dog would
*/
void OnAlarm(int signo)
{
	printf("\nRecvd alarm signal!\n\n");
	int i;
	for (i = 0; i < numProcessors; i++)
	{
		if (!TerminateProcess(processes[i], CHILD_PROC_TERMINATION_CODE))
		{
			ErrorExit(TEXT("Could not kill process"));
		}
	}
}

/**
* Completely and unshamelessly stolen from the MSDN so I could see what errors were occuring
*/
void ErrorExit(LPTSTR lpszFunction)
{
	// Retrieve the system ErrorExit message for the last-ErrorExit code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the ErrorExit message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}

/*
* Completely and unshamelessly stolen from Amit's example code!
*/
void alarm(int *pNumSecs)
{
	LPHANDLE phThread;
	DWORD dwThreadID;

	phThread = CreateThread(
			NULL,							// Security Descriptor (handle not inheritable)
			0,								// initial stack size (default)
			AlarmRun,						// thread function
			pNumSecs,						// thread argument
			0,								// creation option (run immediately)
			&dwThreadID						// thread identifier
	);
		
	if (! phThread) {
		fprintf(stderr, "Unable to create alarm thread.\n");
		ExitProcess(1);
	}
}

/*
* Same with this one
*/
DWORD WINAPI AlarmRun(LPVOID threadData)
{
	int numSecs = *((int *)threadData);
	Sleep(1000 * numSecs);
	raise(SIGINT);

	ExitThread(0);
}

/*
* *whip* *whip* get to work you child processes. don't make me put you in the hot box again!!
*/
void doWork()
{
	srand(GetCurrentProcessId());
	for (;;)
	{
		int i, numInRange = 0;
		for (i = 0; i < 1000000000; i++)
		{
			int num = rand();
			if (num == 21)
			{
				++numInRange;
				if (numInRange % 1000 == 0)
				{
					printf("Process %d count = %d\n", GetCurrentProcessId(), numInRange);
				}
			}
		}
		Sleep(10000);
	}
}
