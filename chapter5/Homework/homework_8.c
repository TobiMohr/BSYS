#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int p[2];  //für pipe p[0] = read, p[1] = write
	
	if(pipe(p) < 0)
		exit(1);
	
	int rc1 = fork();
	if (rc1 < 0) {
		//fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc1 == 0) {
		close(p[0]);		//close read
		dup2(p[1], STDOUT_FILENO);	//redirect stdout to pipe write
		printf("child 1 input");
	} else {
		int rc2 = fork();
		if (rc2 < 0) {
			//fork failed
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc2 == 0) {
			printf("child 2\n");
			close(p[1]);		//close write
			dup2(p[0], STDIN_FILENO);	//redirect stdin to pipe read
			
			char buff[20];
			read(STDIN_FILENO, buff, 20);	// content von stdin in buff lesen
			printf("second child: %s\n", buff);
		} else {
			waitpid(rc1, NULL, 0);
			waitpid(rc2, NULL, 0);
			printf("bye");
		}
	}
	
	return 0;
}