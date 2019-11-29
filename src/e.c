#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


pid_t nfork(int n)
{
	pid_t pid = fork();

	return pid;
}


int main(int argc, char ** argv)
{
	pid_t pid = nfork(1);

	printf("This works yeah ? \nPID: %d ", (int) pid );

	return 0;

}
