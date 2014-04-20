CC=gcc
CFLAGS=-Wall -O 
#CFLAGS=-Wall -g
LFLAGS=-lpthread

all: thread-random

thread-random: thread-random.o timing.o
	$(CC) $(CFLAGS) -o $@ thread-random.o timing.o $(LFLAGS)

clean:
	/bin/rm -f *.o core a.out thread-random
