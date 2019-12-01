#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ncurses.h>

#include "../hdr/data.h"


char * sample_txt = "This some sample text !";


int main(int argc, char ** argv)
{
	data_t * txt = init_data(sample_txt, strlen(sample_txt));
	info_data(txt);
	link_data(txt);
	info_data(txt);
	free_data(txt);
	

//	initscr()
//	noecho();
//	cbreak();
//	keypad(stdscr,true);
//	raw();
//	clear();







	return 0;

}
