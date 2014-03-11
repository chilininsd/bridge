/* C-examples/bitwise-operators/bitmanip.c */

#include <stdio.h>
#include <stdlib.h>

unsigned int isBitISet(unsigned char, int);
unsigned int setBit(unsigned char, int);
unsigned int clearBit(unsigned char, int);
void printResult(int, unsigned int);

int main(int argc, char *argv[])
{
	unsigned char ch = 230; //1110 0110
	int i = 0;
	
	// Check the bit.
	unsigned int isSet = isBitISet(ch, i);
 	printResult(i, isSet);

	// Set the bit.
	unsigned int result = setBit(ch, i);
	isSet = isBitISet(result, i);
	printResult(i, isSet);

	// Clear the bit.
	/*
    result = clearBit(ch, i);
    isSet = isBitISet(result, i);
	printResult(i, isSet);
 	*/
    return 0;
}

void printResult(int i, unsigned int isSet)
{
	if(isSet == 0)
	{
		printf("Bit %d is NOT set\n", i);
	}
	else
	{
		printf("Bit %d is set\n", i);
 	}
}

unsigned int isBitISet(unsigned char ch, int i)
{
	unsigned char mask = 1 << i;
    return mask & ch;
}

unsigned int setBit(unsigned char ch, int i)
{
	unsigned char mask = 1 << i;
    return mask | ch;
}

// Un-implemented.
unsigned int clearBit(unsigned char ch, int i)
{
	return 0;
}
