#!/bin/sh 


datafile=$1
prog=$2

/bin/rm -f $prog.log
for i in 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536
do
	echo -n "buffer size = " $i  >> $prog.log
	(time $prog $i $datafile junk)  &>>  $prog.log
	echo >> $prog.log
	/bin/rm -f junk
done

