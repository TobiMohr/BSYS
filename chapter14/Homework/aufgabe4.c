#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int *pointer = (int *) malloc(sizeof(int));
	*pointer = 8;
	printf("%d\n", *pointer);
	return 0;
}