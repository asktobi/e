#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#define SUM_HASH     1
#define HMAC_HASH    2



void * hash(int function, char* input, size_t size);

void * hashstring(int function, char* input)
{
	int i, len = strlen(input);
	int *acc = (int *) malloc(sizeof(int));

	switch(function)
	{
		case SUM_HASH :
		
			for (i = 0; i <= len; i++)
			{
				*acc += input[i];
			}

			return acc;
		case HMAC_HASH :

		default:
	
			return NULL;
	
	}
	//Should never get to this point right ?
	//Compiler should optimize it out anyway
	return NULL;	
}


