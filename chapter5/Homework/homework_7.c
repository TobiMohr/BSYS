#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int rc = fork();
	
	if (rc < 0)
	{
		//fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		close(STDOUT_FILENO);
		printf("child\n");
	} else {
		wait(NULL);
		printf("parent\n");
	}
	
	return 0;
}