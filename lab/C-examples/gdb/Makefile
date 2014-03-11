
CC=gcc
CFLAGS=-Wall -g  


all: arrays strings testlists  faulty1 loop


faulty1: faulty1.o
	$(CC) $(CFLAGS) -o $@ $<

arrays: arrays.o
	$(CC) $(CFLAGS) -o $@ $<

strings: strings.o
	$(CC) $(CFLAGS) -o $@ $<


testlists: test-lists.o lists.o
	$(CC) $(CFLAGS) -o $@ test-lists.o lists.o


loop: loop.o
	$(CC) $(CFLAGS) -o $@ $<
	

clean:
	rm --force testlists strings arrays *.o core a.out loop faulty1
