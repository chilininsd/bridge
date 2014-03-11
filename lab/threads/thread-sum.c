

#include <unistd.h>
#include <stdlib.h>
/*#include <jemalloc/jemalloc.h>*/
#include <stdio.h>
#include <sysexits.h>
#include <pthread.h>
#include <string.h>

void *partial_sum(void *ptr); 
int *values;
int n;
int result[2]; /* partial sums arrays */

  
int  main( int argc, char **argv)
{
	int i;
    pthread_t thread1, thread2;
     
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <n> \n", argv[0]);
		exit(EX_USAGE);
	}
	n = atoi(argv[1]);
	values = (int *) malloc(sizeof(int)*n);
	for (i=0; i<n; i++)
		values[i] = 1;


    pthread_create(&thread1, NULL, partial_sum, (void *) "1");
    pthread_create(&thread2, NULL, partial_sum, (void *) "2");
  
	pthread_join(thread1, NULL);  
	pthread_join(thread2, NULL);  

	printf("Total sum = %d \n", result[0] + result[1]);
    exit(EXIT_SUCCESS);
}

void *partial_sum(void *ptr)
{
    char *message;
	int sum;
	int i;
	int start, end, index;

    message = (char *) ptr;
    printf("%s ", message);

	sum = 0;
	if (strcmp(message,"1") == 0)  {
		index = 0;
		start = 0;
		end = n/2;
	} else {
		index = 1;
		start = n/2 + 1;
		end = n - 1;
	}

	for (i=start; i<=end; i++)
		sum += values[i];
	
	result[index] = sum;
	pthread_exit(NULL);
} 


