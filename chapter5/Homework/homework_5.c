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
		int p = wait(NULL);
		printf("(%d) child: %d\n", getpid(), p);
	} else {
		int p = wait(NULL);
		printf("(%d) parent: %d\n", getpid(), p);
	}
	
	return 0;
}