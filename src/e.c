#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ncurses.h>

#include "../hdr/data.h"





int main(int argc, char ** argv)
{
	char * blah = "Is this working ?";
	
	data_t * test = w_data( blah, strlen(blah) );
	p_data(test);
	



	return 0;

}
