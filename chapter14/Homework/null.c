#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int *pointer = (int *) malloc(sizeof(int));
	pointer = NULL;
	printf("%d\n", *pointer);
	*pointer;
	free(pointer);
	return 0;
}