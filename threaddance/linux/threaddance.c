#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>  
#include <sys/times.h> 
#include <sys/time.h>  
#include <pthread.h>

#define RANDOM_BUFFER 32
#define CACHE_LINE 256

void generateRandomNumbers(long long, int, struct random_data*);  
void * run(void*);  
double getMilliSeconds();

struct thread_arg {
    int id;
    struct random_data* random;
};

void generateRandomNumbers(long long int count, int seed, struct random_data* random)  
{
	long long int i;
	int x;

	srandom_r(seed, random);
    for (i = 0; i < count; i++)
		random_r(random, &x);
}

long long int randomCount;
int numThreads;
int main(int argc, char **argv)
{
    pthread_t *tid; 
    struct random_data* rand_states;
    char* rand_statebufs;
    struct thread_arg* threadArgs;

    double timeStart = 0;
    double timeElapsed = 0;

  	if (argc < 3) {
        fprintf(stderr, "Usage: %s <numberOfRandoms> <numberOfThreads>\n" ,argv[0]);
        exit(1);
    }

    //initialization
    sscanf(argv[1],"%lld",&randomCount); 
    sscanf(argv[2],"%d",&numThreads); 

    tid = (pthread_t *) malloc(sizeof(pthread_t) * numThreads);
    threadArgs = (struct thread_arg*) malloc(sizeof(struct thread_arg) * numThreads);
    rand_states = (struct random_data*)malloc(sizeof(struct random_data) * numThreads * CACHE_LINE);
    rand_statebufs = (char*)malloc(RANDOM_BUFFER * numThreads * CACHE_LINE);

    //begin timing
    timeStart = getMilliSeconds();

    int i;
    for (i=0; i<numThreads; i++) {
        //initialize random datas
        initstate_r(i, &rand_statebufs[i*CACHE_LINE], RANDOM_BUFFER, &rand_states[i*CACHE_LINE]);

        //set up thread arguments
        struct thread_arg* t = &threadArgs[i];
        t->id = i;
        t->random = &rand_states[i*CACHE_LINE];

        pthread_create(&tid[i], NULL, run, (void *)t);
    }

    for (i=0; i<numThreads; i++)
        pthread_join(tid[i], NULL);

    timeElapsed = getMilliSeconds() - timeStart;
    printf("%lld numbers generated, elapsed time:  %lf seconds\n",randomCount, (double)(timeElapsed/1000.0));
    fflush(stdout);

    free(tid);
    free(rand_states);
    free(rand_statebufs);
    free(threadArgs);

    exit(0);
}

void *run(void *ptr)
{
    struct thread_arg* args = ptr; 
    generateRandomNumbers((int)(randomCount/numThreads), args->id, args->random);
    pthread_exit(NULL);
}

