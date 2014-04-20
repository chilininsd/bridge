
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>  // must include stdio  for pvm3.h to compile correctly
#include <windows.h>

void generateRandomNumbers(long long, int);  
DWORD WINAPI Run(LPVOID arg);
DWORD WINAPI getMilliSeconds();

struct thread_arg {
    int id;
};

void generateRandomNumbers(long long int count, int seed)  
{
	long long int i;
	int x;

	//rand_s the supposedly thread safe RNG for Windows is unuseably slow
	for (i = 0; i < count; i++)
		rand(&x);
}

long long int randomCount;
int numThreads;
int main(int argc, char **argv)
{
	LPHANDLE* tid;
	DWORD* dwThreadIDs;
    struct thread_arg* threadArgs;

    WORD timeStart = 0;
    WORD timeElapsed = 0;

  	if (argc < 3) {
        fprintf(stderr, "Usage: %s <numberOfRandoms> <numberOfThreads>\n" ,argv[0]);
        exit(1);
    }

    //initialization
    sscanf(argv[1],"%lld",&randomCount); 
    sscanf(argv[2],"%d",&numThreads); 

    tid = (LPHANDLE *)malloc(sizeof(LPHANDLE)* numThreads);
	dwThreadIDs = (DWORD *)malloc(sizeof(DWORD)* numThreads);
    threadArgs = (struct thread_arg*) malloc(sizeof(struct thread_arg) * numThreads);
    
    //begin timing
    timeStart = getMilliSeconds();

    int i;
    for (i=0; i<numThreads; i++) {
        //set up thread arguments
        struct thread_arg* t = &threadArgs[i];
        t->id = i;

		//pthread_create(&tid[i], NULL, run, (void *)t);
		tid[i] = CreateThread(
			NULL,						// Security Descriptor (handle not inheritable)
			0,							// initial stack size (default)
			Run,						// thread function
			(void*)t,						// thread argument
			0,							// creation option (run immediately)
			&dwThreadIDs[i]		// thread identifier
			);
		if (tid[i] == NULL) {
			printf("Error in creating thread. Bailing out!\n");
			Sleep(3000);
			ExitProcess(1);
		}
		else {
			printf("Created thread number %d, id %d\n", i, dwThreadIDs[i]);
		}
    }

    for (i=0; i<numThreads; i++)
		WaitForSingleObject(tid[i], INFINITE);

    timeElapsed = getMilliSeconds() - timeStart;
    printf("%lld numbers generated, elapsed time:  %lf seconds\n",randomCount, (double)(timeElapsed/1000.0));
    fflush(stdout);

    free(tid);
    free(threadArgs);
	free(dwThreadIDs);
	exit(0);
}

DWORD WINAPI Run(LPVOID arg)
{
    struct thread_arg* args = arg; 
    printf("I am thread %d with thread id %X going to generate %d numbers \n", args->id, GetCurrentThreadId(), (int)(randomCount/numThreads));
	srand(args->id);
    generateRandomNumbers((int)(randomCount/numThreads), args->id);
	ExitThread(0);
}

