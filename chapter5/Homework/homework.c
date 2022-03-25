#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
	printf("hello world (pid:%d)\n", (int) getpid());
	int x;
	x = 100;
	int rc = fork();
	
	if(rc < 0)
	{
		//fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		//child (new process)
		printf("hello, I am child (pid:%d)\n", (int) getpid());
		x = 8;
		printf("child %d\n", x);
	} else {
		//parent goes down this path (main)
		printf("hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
		x = 10;
		printf("parent %d\n", x);
	}
	printf("%d\n", x);
	return 0;
}
