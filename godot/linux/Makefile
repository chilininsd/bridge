CC=gcc
#CFLAGS= -g   -Wall 
CFLAGS= -O  -Wall 
LFLAGS=-lpthread
JFLAGS=

# Recognize files with .class and .java extensions
.SUFFIXES: .class .java
.java.class:
	javac $(JFLAGS) $<

PROGS=godot

all: $(PROGS)

godot: godot.o
	$(CC) $(CFLAGS) -o $@ godot.o

run: 
	./godot

clean:
	/bin/rm -f *.o $(PROGS) a.out core *.class junk log logfile
