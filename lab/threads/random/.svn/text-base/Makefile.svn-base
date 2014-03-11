

CC=gcc
CFLAGS=-Wall -O
#CFLAGS=-Wall -g
LFLAGS=

all: seq_random

seq_random: seq_random.o timing.o
	$(CC) $(CFLAGS) -o $@ seq_random.o timing.o   $(LFLAGS)

	
clean:
	/bin/rm -f *.o core a.out seq_random
