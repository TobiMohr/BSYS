#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int status;
	int rc = fork();
	char *binaryPath = "/bin/ls";
	char *programName = "ls";
	char *args_binary[] = {binaryPath, NULL};
	char *args_program[] = {programName, NULL};
	char *env[] = {NULL};
	
	if (rc < 0)
	{
		//fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		execl(binaryPath, binaryPath, NULL);
		//execle(binaryPath, binaryPath, NULL, env);
		//execlp(programName, programName, NULL);
		
		//execv(binaryPath, args_binary);
		//execve(binaryPath, args_binary, env);
		//execvp(programName, args_program);
	} else {
		wait( NULL);
		printf("parent end");
	}
	
	return 0;
}