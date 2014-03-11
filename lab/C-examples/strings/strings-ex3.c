
/* C-examples/strings/strings-ex3.c
 *
 * This example shows the proper way to tokenize a string when the tokens
 * need to be passed to other parts of the program.
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_LENGTH = 1024;
const int MAX_TOKENS = 100;

int main(int argc, char **argv)
{
	char *nextToken;
	char *save;
	char *s;
	char **token;
	int numTokens;
	/*char *delimiter = " ;!,\"[]{}`\t\n";*/
	char *delimiter = " ;";

	s = (char *) malloc(sizeof(char) * MAX_LENGTH);
	strcpy(s, " tigger pooh abracadabra woo ;; woo & choo choo");

	/* save a copy because strtok will eat it up */
	save = (char *) malloc(sizeof(char)*(strlen(s)+1));
	strcpy(save, s); 

	token = (char **) malloc (sizeof(char *) * MAX_TOKENS);
	/* tokenize the string s */
	nextToken = strtok(s, delimiter);
	numTokens=0;
	while (nextToken != NULL)
	{
		printf("next token = %s\n", nextToken);
		token[numTokens] = (char *) malloc(sizeof(char) * (strlen(nextToken)+1));
		strcpy(token[numTokens], nextToken);
		numTokens++;
		nextToken = strtok(NULL, delimiter);
	}
	// Now the tokens are copied into token[0..numTokens-1];

	strcpy(s, save); /* restore s */
	return 0;
}
