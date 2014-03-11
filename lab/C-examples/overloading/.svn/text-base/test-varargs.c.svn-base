
/* C-examples/overloading/test-varargs.c */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


void strlist(int n, ...)
{
	va_list ap;
	char *s;

	va_start(ap, n);
	while (1) {
		s = va_arg(ap, char *);
		printf("%s\n",s);
		n--;
		if (n==0) break;
	}
	va_end(ap);
}



int main() {


	printf("Calling with three arguments\n");
	strlist(3, "string1", "string2", "string3");

	printf("Calling with two arguments\n");
	strlist(2, "string1", "string3");

    exit(0);
}

