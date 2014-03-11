#include <stdio.h>

/*
 * Try compiling as
 *  gcc -Wall conversion.c -o conv
 *
 *  and then
 *
 *  gcc -Wall -Wconversion conv.c -o conv
 *
 */

int main()
{
	int m;
	long n = 10000000000;
	float x;
	double y = 2E300;

	m = n;
	x = y;

	printf("%ld %d %le %e\n", n, m, y, x);

	return 0;
}
