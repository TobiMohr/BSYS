#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	fd = open("toopen.txt", O_WRONLY | O_APPEND);
	char child_input[] = "child\n";
	char parent_input[] = "parent\n";
	int rc = fork();
	if(rc < 0)
	{
		//fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		//child (new process)
		for(int i = 0; i < 20; i++)
		{
			write(fd, child_input, sizeof(child_input) - 1);
		}
		exit(0);
	} else {
		//parent goes down this path (main)
		for(int i = 0; i < 20; i++) {
			write(fd, parent_input, sizeof(parent_input) - 1);
		}
	}
	return 0;
}
	