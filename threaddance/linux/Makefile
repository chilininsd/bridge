CC=gcc
CFLAGS=-Wall -O 
#CFLAGS=-Wall -g
LFLAGS=-lpthread

all: threaddance

threaddance: threaddance.o timing.o
	$(CC) $(CFLAGS) -o $@ threaddance.o timing.o $(LFLAGS)

clean:
	/bin/rm -f *.o core a.out threaddance
