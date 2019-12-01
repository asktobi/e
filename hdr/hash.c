#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#define SUM_HASH     1
#define HMAC_HASH    2



void * hash(int function, void * input, size_t n);
{
	size_t i;
	void * hash;

	switch(function)
	{
		case SUM_HASH :

			hash = (uint8_t *) malloc(sizeof(uint8_t));
			for (i = 0; i <= n; i++)
			{
				*(uint8_t *) hash += ((uint8_t *) input)[i];
			}

			return hash;

		case HMAC_HASH :

		default:
	
			return NULL;
	
	}
	//Should never get to this point right ?
	//Compiler should optimize it out anyway
	return NULL;	
}

void * hashstring(int function, char * string)
{
	int i, len = strlen(string);
	int *acc = (int *) malloc(sizeof(int));

	switch(function)
	{
		case SUM_HASH :
		
			for (i = 0; i <= len; i++)
			{
				*acc += string[i];
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


